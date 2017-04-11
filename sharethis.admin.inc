<?php
/**
 * @file
 * Admin functions for ShareThis module.
 */

/**
 * This is the main configuration form for the admin page.
 */
function sharethis_configuration_form($form, &$form_state) {
  // Load the css and js for our module's configuration.
  $my_path = backdrop_get_path('module', 'sharethis');
  backdrop_add_js($my_path . '/js/share-this-form.js');
  backdrop_add_css($my_path . '/css/share-this-form.css');

  $current_options = sharethis_get_all_settings();
  global $base_url;

  // Create the variables related to widget choice.
  $widget_type = $current_options['widget'];

  // Create the variables related to button choice.
  $button_choice = $current_options['buttons'];

  // Create the variables for publisher keys.
  $publisher = $current_options['publisherID'];

  $form = array();
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display'),
  );
  $form['options']['sharethis_button_option'] = array(
    '#required' => TRUE,
    '#type' => 'radios',
    '#options' => array(
      'stbc_large' => t('Large Chicklets 32x32'),
      'stbc_' => t('Small Chicklets (16x16)'),
      'stbc_button' => t('Classic Buttons'),
      'stbc_vcount' => t('Vertical Counters'),
      'stbc_hcount' => t('Horizontal Counters'),
      'stbc_custom' => t('Custom Buttons via CSS'),
    ),
    '#default_value' => $button_choice,
    '#title' => t("Choose a button style:"),
    '#prefix' => '<div class="sharethis-widget-contain">
                    <div class="sharethis-sprite-cover">
                      <img id="stb-sprite" class="sharethis-button-select-sprite ' . $button_choice . '" src="' . $base_url . '/' . $my_path . '/img/preview_sprite.png">
                    </div>
                    <div class="sharethis-widget-pic">
                      <img class="sharethis-button-select-image" src="' . $base_url . '/' . $my_path . '/img/preview_bg.png">
                    </div>',
    '#suffix' => '</div>'
  );

  // Set which services are available.
  $form['options']['sharethis_service_option'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Services to include'),
    '#options' => sharethis_get_services(),
    '#default_value' => $current_options['services'],
  );

  // Set which content types will have ShareThis added.
  $content_types = array();
  $entity_info = entity_get_info('node');
  foreach($entity_info['bundles'] as $bundle => $bundle_info) {
    $content_types[$bundle] = t($bundle_info['label']);
  }
  $form['options']['content']['sharethis_node_types'] = array(
    '#title' => t('Content types that display the ShareThis widget'),
    '#description' => t('The ShareThis links can be ordered with the <a href="@url">Manage Display</a> section for each content type.', array('@url' => url('admin/structure/types'))),
    '#type' => 'checkboxes',
    '#options' => $content_types,
    '#default_value' => $current_options['sharethis_node_types'],
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings'),
    '#description' => t('The advanced settings can usually be ignored if you have no need for them.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['sharethis_late_load'] = array(
    '#title' => t('Load ShareThis after your web-page has completed loading.'),
    '#type' => 'checkbox',
    '#default_value' => config_get('sharethis.settings', 'sharethis_late_load'),
  );
  $form['advanced']['sharethis_publisherID'] = array(
    '#title' => t("Insert a publisher key (optional)."),
    '#description' => t("A publisher key allows you to get detailed analytics about sharing done on your site. When you install the module, a random publisher key is created. You can register the random key with ShareThis by contacting customer support, or if you have an account with <a href='http://www.sharethis.com/account'>ShareThis</a>, your official publisher key can be found under 'My Account'."),
    '#type' => 'textfield',
    '#default_value' => $publisher
  );
  $form['advanced']['sharethis_twitter_suffix'] = array(
    '#title' => t("Twitter suffix"),
    '#description' => t("Add some text to the end of a tweet. Example: <em>via @YourNameHere</em> or <em>#SomeHashtag</em>"),
    '#type' => 'textfield',
    '#default_value' => config_get('sharethis.settings', 'sharethis_twitter_suffix'),
  );
  $form['advanced']['sharethis_twitter_handle'] = array(
    '#title' => t('Twitter Handle'),
    '#description' => t('Twitter handle to use when sharing. Example: <em>@YourNameHere</em>'),
    '#type' => 'textfield',
    '#default_value' => config_get('sharethis.settings', 'sharethis_twitter_handle'),
  );
  $form['advanced']['sharethis_twitter_recommends'] = array(
    '#title' => t('Twitter recommends'),
    '#description' => t('Specify a twitter handle to be recommended to the user.'),
    '#type' => 'textfield',
    '#default_value' => config_get('sharethis.settings', 'sharethis_twitter_recommends'),
  );
  $form['advanced']['sharethis_option_onhover'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display ShareThis widget on hover instead of on click.'),
    '#default_value' => config_get('sharethis.settings', 'sharethis_option_onhover'),
  );
  $form['advanced']['sharethis_option_neworzero'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display a zero (0) instead of "New" in the count for content not yet shared.'),
    '#default_value' => config_get('sharethis.settings', 'sharethis_option_neworzero'),
  );
  $form['advanced']['sharethis_option_shorten'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display either the full or the shortened URL.'),
    '#default_value' => config_get('sharethis.settings', 'sharethis_option_shorten'),
  );
  $form['advanced']['sharethis_cns'] = array(
    '#title' => t('<b>CopyNShare</b> Track shares when a user copies and pastes your website\'s URL or Content'),
    '#description' => t('Please refer the <a href="http://support.sharethis.com/customer/portal/articles/517332-share-widget-faqs#copynshare" target="_blank">CopyNShare FAQ</a> for more details.'),
    '#type' => 'checkboxes',
    '#prefix' => '<div id="st_cns_settings">',
    '#suffix' => '</div>',
    '#options' => array(
      'donotcopy' => t('Track Content copy'),
      'hashaddress' => t('Track URL copy'),
    ),
    '#default_value' => $current_options['sharethis_cns'],
  );
  $form['advanced']['sharethis_cns']['donotcopy']['#description'] = t('When a user copies text within your site, ShareThis adds a "See more: yourURL.com #SThashtag" after the pasted text.');
  $form['advanced']['sharethis_cns']['hashaddress']['#description'] = t('ShareThis adds a special #SThashtag at the end of your address bar URL to keep track of where your content is being shared on the web.');

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Form validation handler for sharethis_configuration_form().
 */
function sharethis_configuration_form_validate($form, &$form_state) {
  // Additional filters for the option extras input
  $form_state['values']['sharethis_option_extras'] = (isset($form_state['values']['sharethis_option_extras'])) ? $form_state['values']['sharethis_option_extras'] : array();

  // Sanitize the publisher ID option.  Since it's a text field, remove anything that resembles code
  $form_state['values']['sharethis_publisherID'] = filter_xss($form_state['values']['sharethis_publisherID'], array());

  // Ensure default value for twitter suffix
  $form_state['values']['sharethis_twitter_suffix'] = (isset($form_state['values']['sharethis_twitter_suffix'])) ? $form_state['values']['sharethis_twitter_suffix'] : '';

  // Ensure default value for twitter handle
  $form_state['values']['sharethis_twitter_handle'] = (isset($form_state['values']['sharethis_twitter_handle'])) ? $form_state['values']['sharethis_twitter_handle'] : '';

  // Ensure default value for twitter recommends
  $form_state['values']['sharethis_twitter_recommends'] = (isset($form_state['values']['sharethis_twitter_recommends'])) ? $form_state['values']['sharethis_twitter_recommends'] : '';
}

/**
 * Form submission handler for sharethis_configuration_form().
 */
function sharethis_configuration_form_submit($form, &$form_state) {
  // Remove items we aren't interested in.
  form_state_values_clean($form_state);

  // Save the config.
  $config = config('sharethis.settings');
  foreach ($form_state['values'] as $key => $value) {
    $config->set($key, $value);
  }
  $config->save();

  backdrop_set_message(t('The configuration options have been saved.'));
}
