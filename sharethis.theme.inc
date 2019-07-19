<?php
/**
 * @file
 * Theme functions for ShareThis module.
 */

/**
 * Generates markup for ShareThis widget.
 */
function theme_sharethis_widget($variables) {
  $property = $variables['property'];
  $product = $variables['product'];

  $url = '//platform-api.sharethis.com/js/sharethis.js#property=' . $property . '&product=' . $product;
  backdrop_add_js($url, array(
    'type' => 'external',
    'async' => TRUE,
    'scope' => 'footer'));

  return '<div class="sharethis-inline-share-buttons"></div>';
}
