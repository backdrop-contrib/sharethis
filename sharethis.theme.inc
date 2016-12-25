<?php
/**
 * @file
 * Theme functions for ShareThis module.
 */

/**
 * Generates markup for ShareThis widget.
 *
 * @param  (array) $variables
 *   Settings for ShareThis widget containing keys:
 *   - url: Absolute URL for the page to share.
 *   - title: Page title for sharing.
 *   - classes: CSS classes to add to the containing wraoer.
 *   - options: Complete set of options stored in configuration, including:
 *     - buttons: Type of buttons to render.
 *     - services: Array of services representing each button.
 *     - twitter suffix: Something to end to the end of Tweets.
 *
 */
function theme_sharethis_widget($variables) {
  // Prepare the wrapper classes.
  $classes = isset($variables['classes'])? $variables['classes'] : array();
  $classes[] = 'sharethis-buttons';

  $type = $variables['options']['type'];
  $all_services = sharethis_get_services();
  $services = isset($variables['options']['services'])? $variables['options']['services'] : array();
  $attributes = array(
    'st_title' => check_plain($variables['title']),
    'st_url' => $variables['url'],
  );

  $markup  = '<div class="' . implode(' ', $classes) . '">';
  $markup .= "  <div class='sharethis-wrapper'>";
  foreach ($services as $service => $status) {
    if ($status) {
      // Complete the attributes.
      $attributes['class'] = array('st_' . $service . '_' . $type);
      $attributes['displayText'] = $all_services[$service];
      // Special handling for twitter.
      switch ($key) {
        case 'twitter':
          $attributes['st_title'] = empty($variables['options']['twitter_suffix']) ? $title : $title . ' ' . check_plain($variables['options']['twitter_suffix']);
          $attributes['st_via'] = $data_options['twitter_handle'];
          $attributes['st_username'] = $data_options['twitter_recommends'];
          break;
      }
      $markup .= '  <span' . backdrop_attributes($attributes). '></span>';
    }
  }
  $markup .= '  </div>';
  $markup .= '</div>';

  // Build a renderable widget.
  $build = array(
    '#type' => 'markup',
    '#markup' => $markup,
  );
  // Attach necessary JS.
  sharethis_include_js($build, $variables['options']);

  return drupal_render($build);
}
