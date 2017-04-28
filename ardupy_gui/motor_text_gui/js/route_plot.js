
var update_nodenumbers = function(){
    var n_nodes = $('.path_node').length;
    if(n_nodes == 0){ 
        $('#no_nodes').show();
    }else{
        var count = 1;
        $('.node_num').each(function(){
            $(this).html(count+'.');
            count++;
        });
        var count = 1;
        $('.path_node').each(function(){
            $(this).attr('num',count);
            count++;
        });
    }
};

var coord_keydown = function(event){
   if(event.keyCode == 13)
       $(this).siblings('.wait').focus(); 

   if((event.key == ' ' && $(this).val().indexOf(' ') != -1) || 
      (event.key == ',' && $(this).val().indexOf(',') !=-1)){
       event.preventDefault();
       $(this).siblings('.wait').focus(); 
   } 
}

var wait_keydown = function(event){
  if(event.keyCode == 13 || event.key == ' ' ||
          (event.keyCode == 9 && !event.shiftKey)){
      event.preventDefault();
      var next_node = 1+Number($(this).siblings('.node_num').html());
      $('.node_num:contains("'+next_node+'")').siblings('.coord').focus();
      //check that the focus was moved off this
      if($(this).is(':focus')){
          append_node();
          var next_node = 1+Number($(this).siblings('.node_num').html());
          $('.node_num:contains("'+next_node+'")').siblings('.coord').focus();
      }
  }
};

var form_verify = function(form,regex){
    if(regex.test(form.val())){
        form.removeClass('alert-danger');
    } else {
        form.addClass('alert-danger');
    }
};
var append_node = function(idx){
    $('#no_nodes').hide();
    var n_nodes = $('.path_node').length+1;
    var coord_id = "coord_"+n_nodes;
    var wait_id = "wait_"+n_nodes;
    var new_node = `<li class="col-12 path_node" num=${n_nodes}>
          <div class="row">
            <div class="col-12">
                <span>
                <span class="node_num">${n_nodes}.</span>
                Go to <input class="coord" id=${coord_id} placeholder="     ," type="text">,
                wait <input class="wait" id=${wait_id} type="text">s
                </span>

                <span class='node_opts'>
                   <b class='node_add node-click'>+</b>
                   <span class='node_close node-click'>&#10006;</span>
                </span>
            </div>
           </div>
          </li>`;

    if(idx == undefined){
        $('#path_nodes').append(new_node);
    }else{
        idx.after(new_node); 
    }
    //unbind previous function attachments so that things are
    //only called once
    $('.node_close, .node_add').unbind('click');

    $('.node_close').click(function(){
        $(this).closest('.path_node').remove();
        update_nodenumbers();
    });
    
    $('.node_add').click(function(){
        append_node($(this).closest('.path_node'));
        update_nodenumbers();
    });

    //unbind previous function attachments so that things are
    //only called once
    $('.coord, .wait').unbind('keydown').unbind('focusout');

    $('.coord').keydown(coord_keydown);
    $('.coord').focusout(function(){form_verify($(this),/^\s*,*[0-9]+[,|\s]+[0-9]+\s*,*$/)});
    $('.wait').keydown(wait_keydown);
    $('.wait').focusout(function(){form_verify($(this),/^\s*,*[0-9]+\s*,*$/)});
 
    //focus the first empty coord
    $($('.coord').get().reverse()).each(function(){
        if(!$(this).val()){
            $(this).focus();
        }
    }); 
    update_nodenumbers();
};



$(document).ready(function(){
    $('#path_nodes').sortable({update:update_nodenumbers});
    $('#add_node').click(function(){append_node()});
    $('#clear_nodes').click(function(){
        save_nodes();
        $('#path_nodes').empty();
        $('#no_nodes').show();

    });
    $(window).bind("beforeunload", function(){
        save_nodes();
    });
    restore_nodes(append_node);
});
