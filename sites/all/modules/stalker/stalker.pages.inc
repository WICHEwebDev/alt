<?php
//$Id$

/**
 * @file
 * 
 * Menu callbacks for Stalker Module.
 * 
 */


/**
 * page callback function for user/%user/stalkers menu path
 * 
 * @param $account
 * @return unknown_type
 */
function stalker_user_page($account) {
	
	//$result = db_query("SELECT stalker_uid, view_count FROM {stalker} WHERE profile_uid = %d ORDER BY view_count DESC", $account->uid );
	
	//change the sql to limit the number of stalkers to the top 5.
	$sql = "SELECT stalker_uid, view_count FROM {stalker} WHERE profile_uid = %d AND view_count > %d ORDER BY view_count DESC";
	$result = db_query_range($sql, $account->uid, variable_get('stalker_threshold',1), 0, 5);
	$items = array();
	
	while ($row = db_fetch_object($result)){
		$viewer = user_load($row->stalker_uid);
		if ( !variable_get('stalker_identity',FALSE)){
			//call the username themeable function to convert this to the username (theme_username($user))
			$items[] = theme('username', $viewer) . " : " . $row->view_count;
		}
		else {
			$items[] = variable_get('anonymous', t('Anonymous')) . " : " . $row->view_count;	
		}
	}
	//the theme_item_list function (see api) takes an array.
	return theme('item_list', $items);
}



