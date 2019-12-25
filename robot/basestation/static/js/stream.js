$(document).ready(function () {

    const STREAM_OFF = '../static/images/stream-offline.jpg'

    function getStreamURL(streamName) {
        // this URL is not going to work currently because:
        // 1. It is hardcoded to localhost. Instead it should use the getRoverIP() helper function for the IP like in camera.js:
        // 'http://' + getRoverIP() + ':8080/stream?topic=/cv_camera/image_raw'
        // the topic names will be either 'armScienceCam', 'frontCam', 'rearCam', instead of 'ArmCamera', 'FrontCamera', 'RearCamera'
        return 'http://localhost:8080/stream?=topic=/' + streamName + '/image_raw'
    }

    $('#arm-stream-btn').on('click', function (event) {
        if ($('#arm-stream-btn').is(':checked')) {
            $('img#arm-camera-feed')[0].src = getStreamURL('ArmCamera')
        } else {
            $('img#arm-camera-feed')[0].src = STREAM_OFF
        }
    })
    $('#front-stream-btn').on('click', function (event) {
        if ($('#front-stream-btn').is(':checked')) {
            $('img#front-camera-feed')[0].src = getStreamURL('FrontCamera')
        } else {
            $('img#front-camera-feed')[0].src = STREAM_OFF
        }
    })

    $('#rear-stream-btn').on('click', function (event) {
        if ($('#rear-stream-btn').is(':checked')) {
            $('img#rear-camera-feed')[0].src = getStreamURL('RearCamera')
        } else {
            $('img#rear-camera-feed')[0].src = STREAM_OFF
        }
    })
})
