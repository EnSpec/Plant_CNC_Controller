/* Script for index.html, contains functions that pass form data into
 * Python controller, which then parses it into serial data for arduino
 */
val_or_placeholder = function(elem){
    return elem.val() || elem.attr('placeholder');
}
$(document).ready(function(){
    setInterval(function(){
        //send a no-op byte to the arduino so SerialInts knows it's connected
        external.send('n',false)
        //poll the arduino's serial port for a response once every .5 seconds
        //TODO: Move this to the python module - it will be a lot of work
        external.echo(function(py_text,py_callback){
            if(py_text != KEY_CODES.EMPTY_BUFFSTR){
                $('#outdiv').html($('#outdiv').html()+py_text+'\n');
                //might eventually stop working
                    if(!$('#outdiv').is(':focus'))
                        $('#outdiv').scrollTop(9999999);
            }
        });
    },500);

    external.set_serial_err(function(err_msg,py_callback){
        alert(err_msg);
    });

    $('#tty').change(function(){
        external.set_serial_port($(this).val());
    });

    $('#scan').click(function(){
        external.get_tty_options(function(py_data){
            $('#tty>option').each(function(){$(this).remove()});
            for(item in py_data){
                $('#tty').append('<option>'+py_data[item]+'</option>');
            }
        });
        $('#tty').trigger('change'); 
    });


    $('#scan').trigger('click');
    setTimeout(function(){$('#tty').trigger('change');},500); 

    $('#send').click(function(){
        external.send_coords(val_or_placeholder($('#instr')));
    });

    $('#set_delay').click(function(){
        external.send_delay(val_or_placeholder($('#delay_val')));
    });

    $('#up').click(function(){ external.send_coords('200,0',3); });
    $('#dn').click(function(){ external.send_coords('-200,0',3); });
    //$('#left').click(function(){ external.send_coords('0,-200',3); });
    //$('#right').click(function(){ external.send_coords('0,200',3); });
    $(window).keydown(function(event){
        switch(event.key){
            case "ArrowUp":
                $('#up').addClass('active').trigger('click');
                setTimeout(function(){$('#up').removeClass('active')},500);
                break;
            case "ArrowDown":
                $('#dn').addClass('active').trigger('click');
                setTimeout(function(){$('#dn').removeClass('active')},500);
                break;
            case "ArrowLeft":
                $('#left').addClass('active').trigger('click');
                setTimeout(function(){$('#left').removeClass('active')},500);
                break;
            case "ArrowRight":
                $('#right').addClass('active').trigger('click');
                setTimeout(function(){$('#right').removeClass('active')},500);
                break;
        }
    });
});
