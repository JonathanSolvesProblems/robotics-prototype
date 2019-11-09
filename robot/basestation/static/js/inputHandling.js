if (
   millisSince(lastCmdSent) > PING_THROTTLE_TIME &&
   !$('#servo-val').is(':focus')) {
        Mousetrap.bind('p',() => {
            console.log('Mousetrap triggered ping')
            pingDevice('Rover')
            lastCmdSent = new Date().getTime()
        } );
    }
if (!$('#servo-val').is(':focus')) {

Mousetrap.bind('i',() => {
    //Increase max throttle
    lightUp('#max-throttle-increase > button')
    console.log('max-throttle-increase')
    maxSoftThrottle += maxThrottleIncrement
    if (maxSoftThrottle > MAX_THROTTLE_SPEED) {
        maxSoftThrottle = MAX_THROTTLE_SPEED
    }
    $('#max-throttle-speed').text(maxSoftThrottle)
    lastCmdSent = new Date().getTime()
})

Mousetrap.bind('j',() => {
    //Decrease max steering
    lightUp('#max-steering-decrease > button')
    maxSoftSteering -= maxSteeringIncrement
    if (maxSoftSteering < 0) {
      maxSoftSteering = 0
    }
    $('#max-steering-speed').text(maxSoftSteering)
    lastCmdSent = new Date().getTime()
})

Mousetrap.bind('k',() => {
    //increase max steering
    lightUp('#max-steering-increase > button')
    maxSoftSteering += maxSteeringIncrement
    if (maxSoftSteering > MAX_STEERING_SPEED) {
      maxSoftSteering = MAX_STEERING_SPEED
    }
    $('#max-steering-speed').text(maxSoftSteering)
    lastCmdSent = new Date().getTime()
})

Mousetrap.bind('l',() => {
    //list all commands
    printCommandsList()
    lastCmdSent = new Date().getTime()
})

Mousetrap.bind('q',() => {
    //stop
    sendRoverCommand('stop')
})

Mousetrap.bind('u',() => {
    //decrease max throttle
    lightUp('#max-throttle-decrease > button')
    maxSoftThrottle -= maxThrottleIncrement
    if (maxSoftThrottle < 0) {
      maxSoftThrottle = 0
    }
    $('#max-throttle-speed').text(maxSoftThrottle)
    lastCmdSent = new Date().getTime()
})

}

// no throttling necessary as since keydown events are throttled
// those keys will not change color and the following code will only set it to it's default color
Mousetrap.bind('o',() => {dim('#stop-motors-btn'); console.log('dim o');},'keyup');
Mousetrap.bind('a',() => {dim('#rover-left > button'); console.log('dim a');},'keyup');
Mousetrap.bind('w',() => {dim('#rover-up > button')},'keyup');
Mousetrap.bind('d',() => {dim('#rover-right > button')},'keyup');
Mousetrap.bind('s',() => {dim('#rover-down > button')},'keyup');
Mousetrap.bind('i',() => {dim('#max-throttle-increase > button')},'keyup');
Mousetrap.bind('u',() => {dim('#max-throttle-decrease > button')},'keyup');
Mousetrap.bind('k',() => {dim('#max-steering-increase > button')},'keyup');
Mousetrap.bind('j',() => {dim('#max-steering-decrease > button')},'keyup');
Mousetrap.bind('l',() => {dim('button#list-all-rover-cmds')},'keyup');
