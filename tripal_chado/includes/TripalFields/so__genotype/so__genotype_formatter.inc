<?php

class so__genotype_formatter extends TripalFieldFormatter {
  // The default lable for this field.
  public static $default_label = 'Genotype';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('so__genotype');

  // The list of default settings for this formatter.
  public static $default_settings = array();
  /**
   *
   * @see TripalFieldFormatter::settingsForm()
   */
  public function settingsForm($view_mode, $form, &$form_state) {

  }

  /**
   *
   * @see TripalFieldFormatter::view()
   */
  public function view(&$element, $entity_type, $entity, $langcode, $items, $display) {
    // Get the settings
    $settings = $display['settings'];

    $headers = array('Name', 'Description', 'Type');
    $rows = array();

    foreach ($items as $delta => $item) {
      $genotype = $item['value'];
      if (!$genotype) {
        continue;
      }

      // Get the field values
      $genotype_name = $genotype['name'];
      $description = $genotype['description'];
      $type = $genotype['type'];

      // Add a link i there is an entity.
      if (array_key_exists('entity', $item['value']) and $item['value']['entity']) {
        list($entity_type, $entity_id) = explode(':', $item['value']['entity']);
        $genotype_name = l($genotype_name, "bio_data/" . $entity_id, array('attributes' => array('target' => "_blank")));
      }
      $rows[] = array($genotype_name, $description, $type);
    }

    $table = array(
      'header' => $headers,
      'rows' => $rows,
      'attributes' => array(
        'id' => 'tripal_linker-table-genotype-object',
        'class' => 'tripal-data-table'
      ),
      'sticky' => FALSE,
      'caption' => "",
      'colgroups' => array(),
      'empty' => 'No genotypes available.',
    );
    $content = theme_table($table);
    if (count($items) > 0) {
      // once we have our table array structure defined, we call Drupal's theme_table()
      // function to generate the table.
      $element[0] = array(
        '#type' => 'markup',
        '#markup' => $content,
      );
    }
  }
}