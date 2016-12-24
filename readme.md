ShareThis
==========

Integration with the ShareThis social bookmarking utility on selected content types.

The code for this project was based on the original share project for Drupal 5.x. It
has been trimmed down to only work with the ShareThis system, and not require any 
additional modules to work properly.

Features:
* Customize your ShareThis code using the STAPI
* Select node types you wish to display ShareThis module on
* Choose to display in $teaser view or not
* Choose to display the ShareThis link in either the $link items, or in the $node->content itself
* Customize the weight of the ShareThis link if in $node placement
* Uses the ShareThis jQuery plugin so the ShareThis servers are queried after page rendering
* Place a ShareThis block anywhere on your site
* Views integration

Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules
  
- You need social media knowledge and probably social media accounts/API keys for 
  this module to provide value.

Known Issues
------------

There are many, many options to this module and not all of them have been tested for 
Backdrop CMS yet.

Coming from Drupal?
-------------------

Using a different way to append Sharethis to the page than the theme_mymodule function in the original Drupal module.

Current Maintainers
-------------------

- biolithic <https://github.com/biolithic>
- seeking additional maintainers

Credits
-------

- Maintained for Drupal by [Rob Loach](https://www.backdrop.org/u/robloach)
- Ported to Backdrop by [biolithic](https://github.com/biolithic)
- This module is based on the ShareThis module for Drupal, originally written and maintained by a large number of contributors.

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
