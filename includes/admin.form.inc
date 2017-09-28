<?php

/**
 * @file
 * Administration page callbacks for the Islandora Usage Stats Callbacks module.
 */

/**
 * Islandora Usage Stats Callbacks administration and configuration form.
 *
 * @ingroup forms
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_usage_stats_callbacks_admin_form() {
  $form = array();

  $form['islandora_usage_stats_callbacks_legacy_stats_file_location'] = array(
    '#type' => 'textfield',
    '#title' => t('Legacy statistics file location'),
    '#description' => t('Path to the legacy stats CSV file (must be in \'pid,views,downloads\' format, or leave field blank to use no legacy stats file)'),
    '#default_value' => variable_get('islandora_usage_stats_callbacks_legacy_stats_file_location', ''),
  );

/* This is for later
  $all_cmodels = islandora_get_content_models();
*/ 

  $form['content_model_wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure which DSID downloads will be tracked.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  module_load_include('inc', 'islandora_usage_stats_callbacks', 'includes/utilities');
  $default_dsids = islandora_usage_stats_callbacks_set_default_dsids();
  $form['content_model_wrapper']['islandora_usage_stats_callbacks_cmodel_dsids'] = array(
    '#type' => 'textarea',
    '#title' => t('Download DSIDs to track'),
    '#rows' => 10,
    '#default_value' => variable_get('islandora_usage_stats_callbacks_cmodel_dsids', $default_dsids),
    '#description' => t("Place each CModel and DSID pair, separated by a |, on its own line. Enter FALSE for CModels with no downloadable datastreams."),
  );


  $form['save_configuration'] = array(
    '#type' => 'submit',
    '#name' => 'saveConfiguration',
    '#default_value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for the admin form for the Islandora Usage Stats Callbacks module.
 *
 * @param array $form
 *   An array representing a form in Drupal.
 * @param array $form_state
 *   An array containing the Drupal form state.
 */
function islandora_usage_stats_callbacks_admin_form_submit($form, &$form_state) {
  if ((file_exists($form_state['values']['islandora_usage_stats_callbacks_legacy_stats_file_location'])) || ($form_state['values']['islandora_usage_stats_callbacks_legacy_stats_file_location'] == '')) {
    variable_set('islandora_usage_stats_callbacks_legacy_stats_file_location', $form_state['values']['islandora_usage_stats_callbacks_legacy_stats_file_location']);
    if ($form_state['values']['islandora_usage_stats_callbacks_legacy_stats_file_location'] != '') {
      drupal_set_message("{$form_state['values']['islandora_usage_stats_callbacks_legacy_stats_file_location']} has been set as the new legacy stats file.");
    }
    else {
      drupal_set_message("You have chosen not to use a legacy stats file.");
    }
    
  }
  else {
    drupal_set_message("No file exists at '{$form_state['values']['islandora_usage_stats_callbacks_legacy_stats_file_location']}'", 'error');
  }
}
