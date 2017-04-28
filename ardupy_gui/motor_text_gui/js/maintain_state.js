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
        external.restore_state(text.attr('id'),
        function(saved_val,py_callback){
           text.html(saved_val); 
        });
    });
}
var restore_forms = function(){
    $('[type=text]').each(function(){
        var form = $(this);
        external.restore_state(form.attr('id'),
        function(saved_val,py_callback){
           form.val(saved_val); 
        });
    });
}
