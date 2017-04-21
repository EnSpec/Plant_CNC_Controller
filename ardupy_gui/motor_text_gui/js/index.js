/* Script for index.html, contains functions that pass form data into
 * Python controller, which then parses it into serial data for arduino
 */
$(document).ready(function(){
    setInterval(function(){
        //send a no-op byte to the arduino so SerialInts knows it's connected
        external.send('n',false)
        //poll the arduino's serial port for a response once every .5 seconds
        //TODO: Move this to the python module - it will be a lot of work
        external.echo(function(py_text,py_callback){
            if(py_text != KEY_CODES.EMPTY_BUFFSTR)
                $('#outdiv').html($('#outdiv').html()+py_text+'\n')
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
            for(item in py_data){
                $('#tty').append('<option>'+py_data[item]+'</option>');
            }
        });
    });



    $('#scan').trigger('click');
    if($('#tty').val() != undefined)
        external.set_serial_port($('#tty').val());
    $('#send').click(function(){
        external.send($('#instr').val());
    });

    $(window).keydown(function(event){
        switch(event.key){
            case "ArrowUp":
                $('#up').addClass('active');
                break;
            case "ArrowDown":
                $('#dn').addClass('active');
                break;
            case "ArrowLeft":
                $('#left').addClass('active');
                break;
            case "ArrowRight":
                $('#right').addClass('active');
                break;
        }
    });

    $(window).keyup(function(event){
        switch(event.key){
            case "ArrowUp":
                $('#up').removeClass('active');
                break;
            case "ArrowDown":
                $('#dn').removeClass('active');
                break;
            case "ArrowLeft":
                $('#left').removeClass('active');
                break;
            case "ArrowRight":
                $('#right').removeClass('active');
                break;
        }
    });
});
