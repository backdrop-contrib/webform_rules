<?php
/**
 * Provide entity-like access to webform submission data.
 * @see webform_rules_condition_data_nid_assertions()
 */
class WebformRulesSubmissionWrapper extends RulesIdentifiableDataWrapper {
// @TODO: implement RulesDataWrapperSavableInterface

  public function __construct($type, $data = NULL, $info = array()) {
    if (!is_null($data)) {
      // If we have a webform submission, add the form values as properties.
      // (If we do not have a submission, properties are added by assertion.
      // @see webform_rules_condition_data_nid_assertions()).
      $info['property info alter'] = array('WebformRulesSubmissionWrapper', 'webformSubmissionValues');
    }
    parent::__construct($type, $data, $info);
    $this->setData($data);
  }

  public static function webformSubmissionValues($wrapper, $property_info) {
    $submission = $wrapper->value();
    $properties = $property_info['properties'];
    if (!empty($submission->nid)) {
      $properties += _webform_rules_component_property_info($submission->nid);
    }
    return array('properties' => $properties);
  }

  protected function setData($data) {
    parent::setData($data);
    if (!is_array($data)) {
      return;
    }
    $submission = current($data);
    if (!isset($submission->sid)) {
      return;
    }
    $s = webform_get_submissions(array('sid' => $submission->sid));
    if (empty($s) || !is_array($s)) {
      return;
    }
    $s = current($s);
    $this->id = $s->sid;
    $this->data = $s;
    $webform = node_load($this->data->entity_id);
    $components = $webform->webform['components'];
    foreach ($s->data as $cid => $val) {
      $c_key = $components[$cid]['form_key'];
      $id = "{$c_key}";
      $this->data->$id = array_values($val);
    }
  }

  protected function extractIdentifier($data) {
    return $data->sid;
  }

  public function getIdentifier() {
    return $this->dataAvailable() && $this->value() ? $this->id : NULL;
  }

  protected function load($data) {
    if (is_array($data)) {
      $sid = $data['sid'];
    }
    else {
      $sid = $data;
    }
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    return webform_get_submissions(array('sid' => $sid));
  }
}
