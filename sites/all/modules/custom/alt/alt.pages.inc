<?php
define('FIVESTAR_COMMENT_DISABLED', 0);
define('COMMENT_PUBLISHED', 0);

function alt_tool_evaluations() {
	$evaluations = alt_get_tool_evaluations();
	
	//header
	$header = array('Tool Name', 'Reviewer', 'Post Date', 'Should we post this tool?', 'Comments');
	$attributes = array();
	$attributes['class'] = 'sample';
	$output = theme_table($header, $evaluations, $attributes);
	
	//dsm($output);
	
    return $output;
	
	
	//return theme('page', $toolReviews);
	//return '<p>'.$toolReviews.'</p>';
	//return '<p>This page is under construction.</p>';	

}


/**
 * Menu callback for path toolsByCategory; Displays list of tools.
 */

/* Replaced by a view.
function alt_tools_by_category(){
	
	//read the tools
	$tools = alt_get_tools_by_category();
	//dsm($tools);

	//the theme_item_list function (see api) takes an array.
	return theme('item_list', $tools);	

	//return t('List of tools will be displayed');
	
}
*/

/**
 * NOT IN USE.
 * Menu callback for showRankings/%forNode; Displays tool_reviews for the node with nid.
 * 
 * @param $nid
 * @return unknown_type
 */
function alt_rankings_page_delete() {
	
	//dsm('in alt_rankings_page');
	//dsm(arg(1));
	$nid = (int) arg(1);
	//dsm($nid);
	
	//if (isset($nid)){
    if ($nid && is_numeric($nid)) {
		$node = node_load($nid);
		//dsm($node);
		$comment = comment_render($node);
	    return $comment;
		//dsm($comment);

/* this code will show the vote info
		//1. read comments. for each, create a comment object.
      //$query_count = 'SELECT COUNT(*) FROM {comments} c WHERE c.nid = %d';
      $query = 'SELECT c.cid as cid, c.pid, c.nid, c.subject, c.comment, c.format, c.timestamp, c.name, c.mail, c.homepage, u.uid, u.name AS registered_name, u.signature, u.signature_format, u.picture, u.data, c.thread, c.status FROM {comments} c INNER JOIN {users} u ON c.uid = u.uid WHERE c.nid = %d';

      $query_args = array($nid);
      if (!user_access('administer comments')) {
        $query .= ' AND c.status = %d';
        //$query_count .= ' AND c.status = %d';
        $query_args[] = COMMENT_PUBLISHED;
      }
      
      
      $query = db_rewrite_sql($query, 'c', 'cid');
      dsm($query);
      dsm($query_args);
      
      $result = db_query($query, $query_args);

      
      while ($comment = db_fetch_object($result)) {
        $comment->name = $comment->uid ? $comment->registered_name : $comment->name;
        $links = module_invoke_all('link', 'comment', $comment, 1);
        drupal_alter('link', $links, $node, $comment);
		
        //2. invoke comment_hook_comment (will hide comments hide them?)
        //comment_hook_comment(&$comment, 'view');
		//3. theme comment and add to output
        
        $output .= theme('comment_view', $comment, $node, $links);
      }
      
    
				
		//return t('working on this');
		dsm($output);
        return $output;
*/
	    				
	}
	else {
		return t('Tool Node information is required in order to view rankings.');	
	}
}
