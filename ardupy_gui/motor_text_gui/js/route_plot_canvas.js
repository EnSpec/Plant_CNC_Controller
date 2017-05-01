const X0 = 860;
const xScale = 3;
const yScale = 3;
var path_plot_svg;
var stepsToCanvasLoc=function(xsteps,ysteps){
    return{
        x:X0-xsteps/xScale,
        y:ysteps/yScale
    };
}

var closet_multiple = function(x,mul){
    if(x%mul > mul/2){
        return x - x%mul + mul;
    }else{
        return x - x%mul;
    }
};
var canvasLocToSteps = function(yloc,xloc){
    var grid = Number($('#grid_size').val());
    var x=(xScale*(X0-xloc))|0;
    var y=(yScale*yloc)|0;
    x= closet_multiple(x,grid);
    y= closet_multiple(y,grid);
    return{
        x:x,
        y:y
    }; 
}
var parse_coords = function(coordstr){
    var splits=[", ",","," "];
    return _.filter(_.map(splits,function(split){
        if(coordstr.split(split).length == 2){
            return{
                x:Number(coordstr.split(split)[0]),
                y:Number(coordstr.split(split)[1]),
            };
        }else{
            return undefined;
        }
    }))[0];
}

var midpoint_marker = function(coord1,coord2){
    var midpt_x = (coord1.x+coord2.x)/2;
    var midpt_y = (coord1.y+coord2.y)/2;
    return (`<circle cx=${midpt_y} cy=${midpt_x} r=5 fill="white" stroke="black"/>`);
};
var label_edges = function(){
    var edge_coords = [
        {x:0,y:0},
        {x:2600,y:0},
        {x:2600,y:2000},
        {x:0,y:2000}
    ];
    _.each(edge_coords,function(coords){
        var move_coords = {
            x:coords.x,
            y:coords.y
        };
        move_coords.x +=(coords.x>0)? 10: -55;
        move_coords.y +=(coords.y>0)?-45*(+coords.x+'(,)'+coords.y).length: 0;
        real_coords = stepsToCanvasLoc(move_coords.x,move_coords.y);
        path_plot_svg.append('text')
            .attr('class','coord_label')
            .attr('x',real_coords.y).attr('y',real_coords.x)
            .attr('font-size',24).attr('font-family','monospace')
            .html('('+coords.x+','+coords.y+')');
    });

}

/*Basically reimplementing jquery-ui.draggable
 */
var DBL = false;
var node_click_func = function(node){

    var key = 0;
    if(DBL){
        DBL = false;
        append_node($('.path_node.active'),false);
        key = 1;
    }else{
        DBL=true;
        setTimeout(function(){DBL=false},400);
    }
    var vbstr = $('#path_plot').attr('viewBox');
    key += Number(node.attr('key'));
    //we're using a weird mix of jQuery and d3, just deal with it for now
    node = path_plot_svg.selectAll('circle[key="'+key+'"]');
    if(!node.classed('active')){
        path_plot_svg.selectAll('circle.node-end.active').
            classed('active',false);
    }
    $('.path_node.active').removeClass('active'); 
    var coordbox = $('.path_node[num="'+key+'"] .coord');
    coordbox.closest('.path_node').addClass('active');
    var viewbox = {
        x0: Number(vbstr.split(' ')[0]),
        y0: Number(vbstr.split(' ')[1]),
        xspan: Number(vbstr.split(' ')[2]),
        yspan: Number(vbstr.split(' ')[3]),
    };
    var mouseinfo=new Object();
    var offset = $('#path_plot').offset();
    var offsetX = offset.left;
    var offsetY = offset.top;
    var width = $('#path_plot').width();
    var height= $('#path_plot').height();
    //glorious 30 fps
    var change_throt = _.throttle(function(){
        coordbox.trigger('change')
    },34);
    $(document).mousemove(function(event){
        mouseinfo.x = (viewbox.x0+viewbox.xspan*
                (event.pageX - offsetX)/width)|0;
        mouseinfo.y = Number(viewbox.y0+viewbox.yspan*
                (event.pageY - offsetY)/height)|0;
        var coords = canvasLocToSteps(mouseinfo.x,mouseinfo.y);
        coordbox.val(coords.x+', '+coords.y);
        change_throt();
    });
    $(document).mouseup(function(){
        $(document).unbind('mousemove');
        //focus on the end of the selected node, 
        //so "enter" will duplicate the current one
        //$(document).unbind('mouseup');
        draw_path();
    });
}
var draw_path = function(){
    var coords= _.filter(_.map($('.coord'),function(coord){
        return parse_coords($(coord).val());    
    }));
    var active_key = Number($('.path_node.active').attr('num'));
    //$('.usr-draw').each(function(){$(this).remove()});
    var doForEachCoord = function(callback){
        var last_coords = stepsToCanvasLoc(0,0);
        _.each(coords,function(coord,idx){
            coord = stepsToCanvasLoc(coord.x,coord.y);
            callback(last_coords,coord,idx);
            last_coords = coord;
        });
    };
    path_plot_svg.selectAll('.usr-draw').remove();
    doForEachCoord(function(last_coords,coord,idx){
        path_plot_svg.append('line')
            .attr("class","usr-draw")
            .attr("x1",last_coords.y).attr("y1",last_coords.x)
            .attr("x2",coord.y).attr("y2",coord.x)
            .attr("stroke","red").attr("stroke-width",10)
            .attr("key",idx+1);
        
    });
    doForEachCoord(function(last_coords,coord,idx){
        var nodeclass = "node-end usr-draw";
        if(active_key == idx+1) nodeclass+=' active';
        path_plot_svg.append('circle')
            .attr("class",nodeclass)
            .attr("cx",coord.y).attr("cy",coord.x)
            .attr("r",7)
            .attr("fill","white").attr("stroke","black")
            .attr("key",idx+1);
    });
    $('.node-end').mousedown(function(){node_click_func($(this),true)});

}

$(document).ready(function(){
    path_plot_svg = d3.select('#path_plot');
    label_edges();
    $(window).keydown(function(event){
        //don't trigger key-based controls if the user is typing
        if($('input:focus').length > 0) return;
        if(!$('.path_node.active .coord').val()) return;
        
        var coords = parse_coords($('.path_node.active .coord').val());
       
        var step = Number($("#grid_size").val());
        switch(event.key){
            case "ArrowUp":
                $('.path_node.active .coord').val(coords.x+step+', '+coords.y);
                break;
            case "ArrowDown":
                $('.path_node.active .coord').val(coords.x-step+', '+coords.y);
                break;
            case "ArrowLeft":
                $('.path_node.active .coord').val(coords.x+', '+(coords.y-step));
                break;
            case "ArrowRight":
                $('.path_node.active .coord').val(coords.x+', '+(coords.y+step));
                break;
            case "Enter":
                append_node($('.path_node.active'),false);
                break;
            case "delete":
                $('.path_node.active .node_close').click();
                break;
        }
        draw_path();
        //$('.path_node.active').trigger('change');
    });
});
