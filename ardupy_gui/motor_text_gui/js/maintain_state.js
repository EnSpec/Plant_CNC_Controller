var save_forms = function(){
    $('[type=text],select').each(function(){
        external.save_state($(this).attr('id'),$(this).val());
    });
};

var save_textareas = function(){
    $('textarea').each(function(){
        external.save_state($(this).attr('id'),$(this).html());
    });
};


var restore_textareas = function(){
    $('textarea').each(function(){
        var text = $(this);
        external.restore_state(text.attr('id'), function(saved_val){
           text.html(saved_val); 
        });
    });
};
//save the values of each node and wait box 
var save_nodes = function(){
    var node_data = []; 
    $('.coord, .wait').each(function(){
        node_data.push($(this).val());
    });
    external.save_state('nodes',node_data);
};
//restores every form on the page
var restore_forms = function(){
    $('[type=text],option').each(function(){
        var form = $(this);
        external.restore_state(form.attr('id'),
        function(saved_val,py_callback){
           if(saved_val) form.val(saved_val); 
        });
    });
};
