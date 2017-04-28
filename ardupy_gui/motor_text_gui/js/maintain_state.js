var save_forms = function(){
    $('[type=text]').each(function(){
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

var save_nodes = function(){
    var node_data = []; 
    $('.coord, .wait').each(function(){
        node_data.push($(this).val());
    });
    external.save_state('nodes',node_data);
};

var restore_nodes = function(callback){
    external.restore_state('nodes',function(saved_nodes){
        if(!saved_nodes) return;
        _.each(saved_nodes,function(node,i){
            if(i%2==0){
                callback();
                $('.coord').last().val(node).trigger('focusout');
            } else {
                $('.wait').last().val(node).trigger('focusout');
            }
        });
    });
};
var restore_forms = function(){
    $('[type=text]').each(function(){
        var form = $(this);
        external.restore_state(form.attr('id'),
        function(saved_val,py_callback){
           form.val(saved_val); 
        });
    });




};
