/**
 * This script modifies the Submitted By group in the Tool content edit page to copy Submitted info into the 
 * Contact field if the Use Same checkbox is checked. 
 *
 *
 * Pmitchell 8/8/11 for WICHE
 */
Drupal.behaviors.WICHE = function (context) {
	//This is the label to be used for the 'use submitter as contact' checkbox
	var boxLabel = "Use my Submitted By information as the Contact For More Information";
	
	//Insert a checkbox onto the page. Checkbox is themeable as class='form-item', 'option', 'form-checkbox'. Change label with above variable (boxLabel).
	var checkbox = "<div id=\"edit-field-tool-contact-same-value-wrapper\" class=\"form-item\"><label for=\"edit-field-tool-contact-same-value\" class=\"option\"><input type=\"checkbox\" class=\"form-checkbox\" value=\"true\" id=\"edit-field-tool-contact-same-value\" name=\"field_tool_contact_same[value]\">" + boxLabel +"</label></div>";
	$(".group-tool-contact").before(checkbox);
	
	$('#edit-field-tool-contact-same-value').change(function() { //if that checkbox changes state
		var useSameValue = $(this).attr('checked'); 
		var greyOut = {
		  style: 'color: #888',
		  readonly: 'readonly'
		}

		if ( useSameValue == true ) { //and the state is true after the change of state
		  //populate the entirety of the group-tool-contact group with the values of group-tool-submitted-by
		  $(".group-tool-contact input").each( function(i) { //for each input in group-tool-contact
		    var nextValue = $(".group-tool-submitted-by input:eq("+ i +")").val(); //find the value of the next input in group-tool-submitted-by
			$(this).attr( 'value', nextValue ); //and set its input to that
		  });
		  
		  $(".group-tool-contact select").each( function(i) { //do the same for selects which are different from input.
		    var nextValue = $(".group-tool-submitted-by select:eq("+ i +")").val(); //find the value of the next input in group -tool-submitted-by
			$(this).attr( 'value', nextValue ); //and set its input to that
		  });
		  
		  //and then disable them
		  //also remove error because it's annoying
		  $(".group-tool-contact input, .group-tool-contact select").attr(greyOut).removeClass("error");

		} else { //if change to false
		  //un-disable them
		  $(".group-tool-contact input, .group-tool-contact select").removeAttr('style').removeAttr('readonly');
		};
		//debug
		//alert('Handler for ' + test + ' called.');
	});
}