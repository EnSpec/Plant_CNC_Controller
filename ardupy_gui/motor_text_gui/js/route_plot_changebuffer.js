const ACTIONS = {
    move:'m',
    remove:'r',
    add:'a',
    clear:'c',
}


const CHANGEBUFFER = {
    idx:0,
    most_recent:0,
    buffer:[],

    curr_action: function(){
        return this.buffer[this.idx].split(',');
    },

    add_action: function(action,duplicates_ok){
        if(duplicates_ok ||  _.last(this.buffer) != action){
            if(this.buffer.length <= this.idx){
                this.buffer.push(action);
            }else{
                this.buffer[this.idx] = action;
            }
            this.idx++;
            this.most_recent = this.idx;
        };
    },
  
    //find the node that was added and delete it 
    undo_add: function(){
        var to_reverse = this.curr_action();
        var key = Number(to_reverse[1]);
        $('.path_node[num="'+key+'"]').remove();
        update_nodenumbers();
    },
    //find the node that was deleted and re-add it 
    redo_add: function(){
        var to_redo = this.curr_action();
        var key = Number(to_redo[1]);
        var new_x = to_redo[2];
        var new_y = to_redo[3];

        append_node($('.path_node[num="'+(key-1)+'"]'));
        var active_info = set_active(key);
        active_info.coordbox.val(new_x+','+new_y);
        update_active_node(active_info);
        
    },

    undo_remove: function(){
        this.redo_add();
    },
    redo_remove: function(){
        this.undo_add();
    },

    undo_move: function(){
        var to_reverse = this.curr_action();
        var key = Number(to_reverse[1]);
        var old_x = to_reverse[2];
        var old_y = to_reverse[3];
        //more funky 'function declared later' stuff 
        //that I don't fully understand
        var active_info = set_active(key);
        active_info.coordbox.val(old_x+','+old_y);
        update_active_node(active_info);
    },

    redo_move: function(){
        var to_redo = this.curr_action();
        var key = Number(to_redo[1]);
        var new_x = to_redo[4];
        var new_y = to_redo[5];

        var active_info = set_active(key);
        active_info.coordbox.val(new_x+','+new_y);
        update_active_node(active_info);

    },

    undo_clear: function(){
        var to_reverse = this.curr_action();
        var x_coord;
        $('#path_nodes').empty();
        _.each(_.rest(to_reverse),function(coord,idx){
            if(idx%2 == 0) x_coord = coord;
            else{
                var new_node = get_node_template();
                new_node.find('.coord').val(x_coord + ',' + coord);
                $('#path_nodes').append(new_node);
            }
        });
        draw_path();
        bind_actions_to_nodes();
    },

    redo_clear: function(){
        $('#path_nodes').empty();
        append_node();
    },

    undo: function(){
        //don't do this if we're out of recorded actions
        if(this.idx == 0) return;
        this.idx--;
        var to_reverse = this.curr_action();

        if(to_reverse[0] == ACTIONS.move) this.undo_move();
        else if(to_reverse[0] == ACTIONS.add) this.undo_add();
        else if(to_reverse[0] == ACTIONS.remove) this.undo_remove();
        else if(to_reverse[0] == ACTIONS.clear) this.undo_clear();
        

    },

    redo: function(){
        //don't do this if we're past the most recent action
        if(this.idx >= this.most_recent) return;
        var to_redo = this.curr_action();
        if(to_redo[0] == ACTIONS.move) this.redo_move();
        else if(to_redo[0] == ACTIONS.add) this.redo_add();
        else if(to_redo[0] == ACTIONS.remove) this.redo_remove();
        else if(to_redo[0] == ACTIONS.clear) this.redo_clear();
        
        this.idx++;

    },
};


//record the location that a node is at when it is placed
var record_add = function(active_info){
    var action = ACTIONS.add+','+active_info.key+','+active_info.coordbox.val();
    CHANGEBUFFER.add_action(action,true);
};

//record the location that a node was at before it was removed
var record_remove = function(remove_info){
    var action = ACTIONS.remove +','+remove_info.key+','+remove_info.coordbox.val();
    CHANGEBUFFER.add_action(action,true);
};

//record the start and end positions of a node when it's moved
var record_move = function(start_info,active_info){
    var action = ACTIONS.move+','+active_info.key+','+start_info.val+','+active_info.coordbox.val();
    CHANGEBUFFER.add_action(action);
};

//record the locations of every node before they get deleted
var record_clear = function(){
    var action = ACTIONS.clear +',' + $('.coord').map(function(){
        return this.value;
    }).get().join(',');
    CHANGEBUFFER.add_action(action,true);
};
$(document).ready(function(){
    $('#nav-undo').click(function(){CHANGEBUFFER.undo()});
    $('#nav-redo').click(function(){CHANGEBUFFER.redo()});
    $(window).keypress("z",function(event){
        if(event.ctrlKey && event.shiftKey){
            CHANGEBUFFER.redo();
        } else if(event.ctrlKey){
            CHANGEBUFFER.undo();
        };
    });
});
