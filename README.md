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
Islandora Usage Stats Callbacks currently requires no configuration. The API becomes accessible when the module is enabled.

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

## Troubleshooting/Issues
If you are having problems with Islandora Usage Stats Callbacks, please contact Bryan J. Brown (bjbrown@fsu.edu).

## Maintainers/Sponsors
Islandora Usage Stats Callbacks was created by [Bryan J. Brown](https://github.com/bryjbrown) for [FSU Libraries](https://www.lib.fsu.edu) in collaboration with [Florida Virtual Campus](https://github.com/flvc).

## Development
Islandora Usage Stats Callbacks can be extended to provide more report types as they become necessary.
If you have a use case for another report type, please file an issue on this GitHub repository with details.

## License
[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
