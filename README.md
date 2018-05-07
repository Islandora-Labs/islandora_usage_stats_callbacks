# islandora_usage_stats_callbacks
*Helper module for exposing islandora_usage_stats data*

## Description
Islandora Usage Stats Callbacks is a helper module that uses the data collected by the Islandora Usage Stats and exposes it via URL callbacks.

## Requirements
This module requires the following modules/libraries:
* [Tuque](https://github.com/islandora/tuque)
* [Islandora](https://github.com/islandora/islandora)
* [Islandora Usage Stats](https://github.com/Islandora/islandora_usage_stats)

## Installation
Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration
Islandora Usage Stats Callbacks currently requires permssions to be set. This is only set for __admin__ by default. The API becomes accessible when the module is enabled.

This will make it available for all user roles including anonymous.
```terminal
# Grant permissions for everyone to see the download count
/var/www/drupal$ drush role-add-perm 'anonymous user' 'access usage stats callbacks api'
/var/www/drupal$ drush role-add-perm 'authenticated user' 'access usage stats callbacks api'
```

## Usage
The Islandora Usage Stats Callback API uses the following pattern:  
`{base url}/islandora_usage_stats_callbacks/{report type}/{pid}`

### object_stats
The current API only supports one report type, `object_stats`, which returns the time and IP address of views and downloads by PID (currently only supports citation, thesis and PDF objects) and exposes them in a structured JSON format:
```json
{  
   "pid":"islandora:1",
   "cmodel":"islandora:sp_pdf",
   "views":[  
      {  
         "time":"1450204717",
         "ip":"128.186.58.122"
      },
      {  
         "time":"1450205392",
         "ip":"128.186.58.122"
      }
   ],
   "downloads":[  
      {  
         "time":"1450385219",
         "ip":"128.186.58.122"
      }
   ]
}
```
The **object_stats** report type was created to meet requirements from  FSU Libraries for an externally accessible API for retrieving views/downloads for an object via pid in order to create email readership reports for faculty with objects in the FSU Research Repository.

### To display on the object's page from the theme's template.php file.
```php
// from within your theme's preprocess page function
function yourThemeName_preprocess_page(&$variables, $hook) {

  // Includes needed module functions
  module_load_include('inc', 'islandora', 'includes/utilities');

  // Retrieve the object (PID from the URL)
  $parsed_request = explode('/', $_SERVER['REQUEST_URI']);

  // PID check to see if this is an object or not
  if (islandora_is_valid_pid(urldecode(end($parsed_request)))) {
    $variables['page']['islandora_object'] = islandora_object_load(urldecode(end($parsed_request)));
    
   // Check if the valid PID is not a collection
    if(!isset($variables['page']['islandora_object']['COLLECTION_POLICY']))
    {
      $islandora_object = $variables['page']['islandora_object'];
      // checks if modules is installed and if user has api access
      if (module_exists('islandora_usage_stats_callbacks') && user_access('access usage stats callbacks api')) {
        global $base_url;
        // grabs the download and view count
        $usage_stats_json = file_get_contents("{$base_url}/islandora_usage_stats_callbacks/object_stats/{$islandora_object->id}");
        $usage_stats_array = json_decode($usage_stats_json, TRUE);
        $views = count($usage_stats_array['views']) + $usage_stats_array['legacy-views'];
        $downloads = count($usage_stats_array['downloads']) + $usage_stats_array['legacy-downloads'];
        $usage_data = array('views' => $views, 'downloads' => $downloads);
        // places strings within page level variables for parcing (optional)
        $variables['page']['object_cmodel'] = $usage_stats_array['cmodel'];
        $variables['page']['usage_views'] = $usage_data['views'];
        $variables['page']['usage_downloads'] = $usage_data['downloads'];
        // Builds the string to append to the content 
        $string_something = '<div id="usage-stats-box"><span class="usage-stats-views">' . $usage_data['views'] . ' views</span><br><span class="usage-stats-downloads">' . $usage_data['downloads'] . ' downloads</span></div>';
        $variables['page']['content']['system_main']['citation.tab']['pdf_download']['#suffix'] = $string_something;
      }
    }
  }
}
```

## Troubleshooting/Issues
If you are having problems with Islandora Usage Stats Callbacks, please contact Bryan J. Brown (bjbrown@fsu.edu).

## Maintainers/Sponsors
Islandora Usage Stats Callbacks was created by [Bryan J. Brown](https://github.com/bryjbrown) for [FSU Libraries](https://www.lib.fsu.edu) in collaboration with [Florida Virtual Campus](https://github.com/flvc).

## Development
Islandora Usage Stats Callbacks can be extended to provide more report types as they become necessary.
If you have a use case for another report type, please file an issue on this GitHub repository with details.

## License
[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
