__WEBRTC API__
==============

WebRTC (Web Real-Time Communication) is a technology which enables Web applications and sites to capture and optionally stream audio and/or video media, as well as to exchange arbitrary data between without requiring an intermediary. The set of standards that comprise WebRTC makes it possible to share data and perform teleconferencing peer-to-peer, without requiring that the user install plug-ins or any other third party software.

WebRTC consists of several interrelated APIs and protocols which work together to achieve this. This documentation you'll find here will help you understand the fundamentals of WebRTC, how to set up and use both data and media connections, and more.

## __INTEROPERABILITY__

Because implementations of WebRTC are still evolving, and because each browser has [different levels of support for codecs](CodecsUsedByWebRTC.md) and WebRTC features, you should strongly consider making use [the Adapter.js library](https://github.com/webrtcHacks/adapter) provided by Google before you begin to write your code.


Adapter.js uses shims and polyfills to smooth over the difference among the WebRTC implementations across the environments supporting it. Adapter.js also handles prefixes and other naming differences to make the entire WebRTC development process easier, with more broadly compatible results. The library is also [available as an NPM package](https://www.npmjs.com/package/webrtc-adapter).

To learn more about Adapter.js, see [Improving compatibility using WebRTC adapter.js](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/adapter.js).

## __WEBRTC CONCEPTS AND USAGE__

WebRTC serves multiple purposes; together with the [Media Capture and Streams API](https://developer.mozilla.org/en-US/docs/Web/API/Media_Streams_API), they provide powerful multimedia capabilities to the Web, including support for audio and video conferencing, file exchange, screen sharing, identity management, and interfacing with legacy telephone systems including support for sending [DTMF](https://developer.mozilla.org/en-US/docs/Glossary/DTMF) (touch-tone dialing) signals. Connections between peers can be made without requiring any special drivers or plug-ins, and can often be made without any intermediary servers.

Connections between two peers are represented by the RTCPeerConnectino interface. Once a connection has been established and opened using RTCPeerConnection, media streams (MediaStreams) and/or channels (RTCDataChannels) can be added to connection.

Media streams can consist of any number of tracks of media information; tracks, which represented by objects based on the MediaStreamTrack interface, may contain one of a number of types of media data, including audio, video, and text (such as sbutitles or even chapter names). Most streams consist of at least one audio track and likely also a video track, and can be used to send and receive both live media or stored media information (such as a streamed movie).

You can also use the connection between two peers to exchange arbitrary binrary data using the RTCDataChannel interface. This can be used for back-channel information, metadata exchange, game status packets, file transfers, or even as a primary channel for data transfer.

more details and links to relevant guides and tutorial needed.

## __WEBRTC REFERENCE__

Because WebRTC provides interfaces that work together to acoomplish a variety of tasks, we have divided up the reference by category. Please see the sidebar for an alphabetical list.

### __CONNECTION SETUP AND MANAGEMENT__

These interfaces, dictionaries, and types are used to set up, open, and manage WebRTC connections. Included are interfaces representing peer media connections, data channels, and interfaces used when exchanging information on the capabilities of each peer in order to select the best possible configration for a two way media connection.

#### __INTERFACES__

__RTCPeerConnection__

Represents a WebRTC connection between the local computer and a remote peer. It is used to handle efficient streaming of data between the two peers.

__RTCDataChannel__

Represents a bi-directional data channel between two peers of a connection.

__RTCDataChannelEvent__

Represents events that occur in relation to ICE candidates with the target, usually an RTCPeerConnection. Only one event is of this type: icecandidate.

__RTCRtpSender__

Manages the encoding and transmission of data for a MediaStreamTrack on an RTCPeerConnectino.

__RTCRtpReceiver__

Manages the reception and decoding of data for a MediaStreamTrack on an RTCPeerConnection.

__RTCTrackEvent__

The interface used to represent a track event, which indicates that an RTCRtpReceiver object was added to the RTCPeerConnection object, indicating that a new incoming MediaStreamTrack was created and added to the RTCPeerConnection.

__RTCSctpTransport__

Provides information which describes a Stream Control Transimission Protocol ([SCTP](https://developer.mozilla.org/en-US/docs/Glossary/SCTP)) transport and also provides a way to access the underlying Datagram Transport Layer Security ([DTLS](https://developer.mozilla.org/en-US/docs/Glossary/DTLS)) transport over which SCTP packets for all of an RTCPeerConnection's data channels are sent and received.

### __DICTIONARIES__

__RTCConfiguration__

Used to provide configuration options for an RTCPeerConnection.

__RTCIceServer__

Defines how to connect to a single [ICE](https://developer.mozilla.org/en-US/docs/Glossary/ICE) server (such as a [STUN](https://developer.mozilla.org/en-US/docs/Glossary/STUN) or [TURN](https://developer.mozilla.org/en-US/docs/Glossary/TURN) server).

__RTCRtpContributingSource__

Contains information about a given contributing source (CSRC) including the most recent time a packet that the source contributed was played out.

### __EVENTS__

__bufferedamountlow__

The amount of data currently buffered by the data channel - as indicatyed by its bufferedAmount property - has decreased to be at or below the channel's minimum buffered data size, as specified by bufferedAmountLowThreshold.

__close__

The data channel has completed the closing process and is now in the closed state. Its underlying data transport is completely closed at this point. You can be notified before closing completes by watching for the closing event instead.

__closing__

The RTCDataChannel has transitioned to the closing state, indicating that it will be closed soon. You can detect the completion of the closing process by watching for the close event.

__connectionstatechange__

The connection's state, which can be accessed in connectionState, has changed.

__datachannel__

A new RTCDataChannel is available following the remote peer opening a new data channel. This event's type is RTCDataChannelEvent.

__error__

An RTCErrorEvent indicating that an error occurred on the data channel.




