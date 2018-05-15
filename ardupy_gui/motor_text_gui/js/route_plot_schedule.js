/*entirely superfluous: make the clockface spin*/
var Spinner = {
    SPIN: false,
    idx: 0,
    faces: ["&#128336;",
            "&#128337;",
            "&#128338;",
            "&#128339;",
            "&#128340;",
            "&#128341;",
            "&#128342;",
            "&#128343;",
            "&#128344;",
            "&#128345;",
            "&#128346;",
            "&#128347;"],

    spinClock: function(){
        Spinner.idx+=1;
        if(Spinner.idx == Spinner.faces.length)
            Spinner.idx = 0;
        $('#sched').html("Schedule "+Spinner.faces[Spinner.idx]+" ...");
    },

    startSpin: function(){
        Spinner.spinf = setInterval(function(){Spinner.spinClock()},500);
    },
    stopSpin: function(){
        clearInterval(Spinner.spinf);
    },
};

$(document).ready(function(){

    $('#sched').mouseenter(Spinner.startSpin);
    $('#sched').mouseleave(Spinner.stopSpin);

});
