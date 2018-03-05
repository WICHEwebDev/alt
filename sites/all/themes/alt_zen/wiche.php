<?php

/* This function adds the wiche.js script to pages at the /node/add
 * 
 * Pmitchell 8/8/11 for WICHE
 */
 
function _patrick_preprocess_node(&$variables) {
  //Test function: put output on page 148
  /*
  if ('node' == arg(0) && '148' == arg(1)) {
      drupal_add_js(drupal_get_path('theme', 'alt_zen'). '/js/deborah.js', 'theme');
	  // We need to rebuild the scripts variable with the new script included.
	  $variables['scripts'] = drupal_get_js();
  }
  */
  
  if ('node' == arg(0) && 'add' == arg(1) && 'tool' == arg(2) ) {
	  drupal_add_js(drupal_get_path('theme', 'alt_zen'). '/js/wiche.js', 'theme');
	  // We need to rebuild the scripts variable with the new script included.
	  $variables['scripts'] = drupal_get_js();
  }

}