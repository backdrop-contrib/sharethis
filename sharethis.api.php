<?php
/**
 * @file
 * API functions for sharethis module.
 */

/**
 * Alter hook for available services.
 */
function hook_sharethis_services($services) {
  // Remove services.
  unset($services['sharethis']);
  // Add services.

  // Move facebook to the end.
  unset($services['facebook']);
  $servces['facebook'] = 'Facebook';

  // To determine which services are available for ShareThis, visit
  // http://tools.sharethis.com/get-sharing-tools and select "Website".
  // Go through the steps to generate the buttons you want, and click "get code".
  // You will get a set of span tags that look similar to this one:
  // <span class='st_reddit_large' displayText='Reddit'></span>
  // The key of the $services array should be the center section of the class,
  // and the value of the $services array should be the displayText attribute.

  // Add new services.
  $servces['reddit'] = 'Reddit';
  $servces['googleplus'] = 'Google +';

  return $services;
}
