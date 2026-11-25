var dragging = false;

$(document).ready(function() {
	$("div.small_proof_content").each(function() {
	  var state = $(this).children(":first").find("span.tactic_state_left");
	  $(this).siblings("div.small_tactic_state").html(state.html());
	});
    $("div.definition_text").click(
           function() {
               $(this).siblings("div.definition_lean").slideToggle()
           })
    $("div.example_text").click(
           function() {
               $(this).siblings("div.example_lean").slideToggle()
           })
    $("div.lemma_text").click(
           function() {
               $(this).siblings("div.lemma_lean").slideToggle()
           })
    $("div.theorem_text").click(
           function() {
               $(this).siblings("div.theorem_lean").slideToggle()
           })
    $("span.proof_item_text").click(
           function() {
               $(this).siblings("div.proof_item_lean").slideToggle()
           })

    $("span.tactic_left").click(
           function() {
               $(this).parents("div.small_proof_content").siblings("div.small_tactic_state").html(
				        $(this).siblings("span.tactic_state_left").html());
           })

    $("span.tactic_right").click(
           function() {
               $(this).parents("div.small_proof_content").siblings("div.small_tactic_state").html(
				        $(this).siblings("span.tactic_state_right").html());
           })
});
