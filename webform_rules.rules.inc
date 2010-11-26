<?php
// $Id$

/**
 * @file
 * Functions for rules integration.
 */

/**
 * Implementation of hook_rules_event_info().
 * @ingroup rules
 */
function webform_rules_rules_event_info() {
  return array(
    'webform_rules_submit' => array(
      'label' => t('After a webform has been submitted'),
      'module' => 'Webform',
      'arguments' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User, who submitted the webform'),
        ),
        'node' => array(
          'type' => 'node',
          'label' => t('The webform node'),
        ),
        'data' => array(
          'type' => 'data',
          'label' => t('The submitted webform data'),
        ),
      ),
    ),
  );
}
