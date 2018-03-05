
// Global Killswitch
if (Drupal.jsEnabled) {
  $(document).ready(function() {  
    // Close
    $(".admin-message a.admin-message-close").click(function() {
      var href = $(this).attr("href");
      $.get(href);
      $(this).parent().slideUp('fast');
      return false;
    });
  });
}
