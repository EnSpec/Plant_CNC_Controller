/*When a modal-triggering button is clicked, load the contents of an
 * associated html file into that modal's body before it is displayed
 */
$(document).ready(function(){
    $('button[data-target="#help-modal"]').click(function(){
        $('#help-modal-body').html('');
        var url = 'help/'+$(this).attr('id')+'.html';
        console.log(url);
        $.get(url).then(function(data){
            $('#help-modal-body').html(data);
        });
    });
});
