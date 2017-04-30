var stepsToCanvasLoc=function(xsteps,ysteps){
    var x = 860-xsteps/3;
    var y = ysteps/3;
    return{
        x:x,
        y:y};
}

var parse_coords = function(coordstr){
    if (coordstr.split(' ').length == 2)
        return{
            x:Number(coordstr.split(' ')[0]),
            y:Number(coordstr.split(' ')[1]),
        };
    else if (coordstr.split(',').length == 2)
        return{
            x:Number(coordstr.split(',')[0]),
            y:Number(coordstr.split(',')[1]),
        };
    else
        return undefined;
}
var draw_path = function(){
    var coords= _.filter(_.map($('.coord'),function(coord){
        return parse_coords($(coord).val());    
    }));
    $('#path_plot').empty();
    var last_coords = stepsToCanvasLoc(0,0);
    _.each(coords,function(coord){
        coord = stepsToCanvasLoc(coord.x,coord.y);
        console.log(last_coords,coord);
        //axes are flipped here
        $('#path_plot').append(`<line x1=${last_coords.y} y1=${last_coords.x} x2=${coord.y} y2=${coord.x}
                  stroke-width="4" stroke="red"/>`);
        last_coords = coord;
    });
    //refresh the whole svg
    $("#canvas-border").html($("#canvas-border").html());
}

