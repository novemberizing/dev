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

An RTCErrorEvent indicating that an error occurred on the RTCtlsTransport. This error will be either dtls-failure or fignerprint-failure.

__gatheringstatechange__

The RTCIceTransport's gather state has changed.

__icecandidate__

An RTCPeerConnectionIceErrorEvent indicating that an error has occurred while gathering ICE candidates.

__iceconnectionstatechange__

Sent to an RTCPeerConnection whenits ICE connection's state - found in the iceconnectionstate property - changes.

__icegatheringstatechange__

Sent to an RTCPeerConnection when its ICE gathering state - found in the icegatheringstate property - changes.

__message__

A message has been received on the data channel. The event is of type MessageEvent.

__negotiationneeded__

Informs the RTCPeerConnection that it needs to perform session megotiation by calling createOffer() followed by setLocalDescription().

__open__

The underlying data transport for the RTCDataChannel has been successfully opened or reopened.

__selectdcandidatepairchange__

The currently-selected pair of ICE candidates has changed for the RTCIceTransport on which the event is fired.

__track__

The track event, of type RTCTrackEvent is sent to an RTCPeerConnection when a new track is added to the connection following the successful negotiation of the media's streaming.

__signalingstatechange__

Sent to the peer connection when its signalingstate has chanaged. This happens as a result of a call to either setLocalDescription() or setRemoteDescription().

__statechange__

The state of the RTCDtlsTransport has changed.

### __TYPES__

__RTCSctpTranportState__

Indicates the state of an RTCSctpTransport instance.

__RTCSessionDescriptionCallback__

Thre RTCSessionDescriptionCallback is passed into the RTCPeerConnection object when requesting it to create offers or answers.

### __IDENTITY AND SECURITY__

These APIs are used to manage user identify and security, in order to authenticate the user for a connection.

__RTCIdentifyProvider__

Enables a user agent is able to request that an identity assertion be generated or validated.

__RTCIdentityAssertion__

Represents the identity of the remote peer of the current connection. If no peer has yet been set and verified this interface returns null. Once set it can't be changed.

__RTCIdentityProviderRegistrar__

Registers an identity provider (idP).

__RTCIdentityEvent__

Represents an identity assertion generated by an identity provider(idP). This is usually for an RTCPeerConnection. The only event sent with this type is identityresult.

__RTCIdentityErrorEvent__

Represents an error associated with the identity provider (idP). This is usually for an RTCPeerConnection. Two events are sent with this type: idpassertionerror and idpvalidationerror.

__RTCCertificate__

Represents a certificate that an RTCPeerConnection uses to authenticate.

### TELEPHONY

These inferfaces and events are related to interactivity with Public-Switched Telephone Networks (PTSNs). They're primarily used to send tone dialing sounds - or packets representing those tones - across the network to the remote peer.

#### __INTERFACE__

__RTCDTMFSender__

Manages the encoding and transmission of Dual-Tone Multi-Frequency (DTMF) signaling for an RTCPeerConnection.

__RTCDTMFToneChangeEvent__

Used by the tonechange event to indicate that a DTMF tone has either begun or ended. This event does not bubble (except where otherwise stated) and is not cancelable (except where otherwise stated).

#### __EVENTS__

__tonechange__

Either a new DTMF tone has begun to play over the connection, or the last tone in the RTCDTMFSender's toneBuffer has been sent and the buffer is now empty. The event's type is RTCDTMFToneChangeEvent.

## __GUIDES__

__[INTRODUCTION TO WEBRTC PROTOCOLS](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Protocols)__

This article introduces the protocols on top of which tghe WebRTC API is built.

__[WEBRTC CONNECTIVITY](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Connectivity)__

A guide to how WebRTC connections work and how the various protocols and interfaces can be used together to build powerful communication apps.

__[LIFETIME OF A WEBRTC SESSION](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Session_lifetime)__

WebRTC lets you build peer-to-peer communication of arbitrary data, audio, or video - or any combination thereof - into a browser application. In this article, we'll look at the lifetime of a WebRTC session, from esablishing the connection all the way through closing the connection when it's no longer needed.

__[ESTABLISHING A CONNECTION: THE PERFECT NEGOTIATION PATTERN](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Perfect_negotiation)__

Perfect negotiation is a design pattern which is recommended for you signaling process to follow, which provides transparency in negotiation while allowing both sides to be either the offerer of the answerer, without significant coding needed to differentiate the two.

__[SIGNALING AND TWO-WAY VIDEO CALLING](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Signaling_and_video_calling)__

A tutorial and example which turns a WebSocket-based chat system created for a previous example and adds support for opening video calls among participants. The chat server's WebSocket connection is used for WebRTC signaling.

__[CODECS USED BY WEBRTC](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/WebRTC_codecs)__

A guide to the codecs which WebRTC requires browsers to support as well as the optional ones supported by various popular browsers. Included is a guide to help you choose the best codecs for your needs.

__[USING WEBRTC DATA CHANNELS](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Using_data_channels)__


This guide covers how you can use a peer connection and an associated RTCDataChannel to exchange arbitrary data between two peers.

__[USING DTMF WITH WEBRTC](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Using_DTMF)__

WebRTC's support for interacting with gateways that link to old-school telephony systems includes support for sending DTMF tones using the RTCDTMFSender interface. This guide shows how to do so.

## __TUTORIALS__

__[IMPROVING COMPATIBILITY USING WEBRTC ADAPTER.JS](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/adapter.js)__

The WEBRTC organization [provides on Github the WEBRTC adapter](https://github.com/webrtc/adapter/) to work around compatibility issues in different browser's WebRTC implementations. The adapter is a JavaScript shim which lets your code to be written to the specification so that it will "just work" in all browsers with WebRTC support.

__[TAKING still photos with WebRTC](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Taking_still_photos)__

This article shows how to use WebRTC to access the camera on a computer or mobile phone with WebRTC support and take a photo with it.

__[A SIMPLE RTCDataChannel SAMPLE](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Simple_RTCDataChannel_sample)__

The RTCDataChannel interface is a feature which lets you open a channel between two peers over which you may send a receive arbitrary data. The API is intentionally similar to the [WebSocket API](https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API), so that the same programming model can be used for each.

## __RESOURCES__

### __PROTOCOLS__

#### __WEBRTC PROPER PROTOCOLS__

- [Application Layer Protocol Negotiation for Web Real Time Communications](https://datatracker.ietf.org/doc/draft-ietf-rtcweb-alpn/)
- [WebRTC Audio Codec and Processing Requirements](https://datatracker.ietf.org/doc/rfc7874/)
- [RTCWeb Data Channels](https://datatracker.ietf.org/doc/draft-ietf-rtcweb-data-channel/)
- [RTCWebData Channel Protocol](https://datatracker.ietf.org/doc/draft-ietf-rtcweb-data-protocol/)
- [Web Real-Time Communication (WebRTC): Media Transport and Use of RTP](https://datatracker.ietf.org/doc/draft-ietf-rtcweb-rtp-usage/)
- [WebRTC Security Architecture](https://datatracker.ietf.org/doc/draft-ietf-rtcweb-security-arch/)
- [Transports for RTCWEB](https://datatracker.ietf.org/doc/draft-ietf-rtcweb-transports/)

#### RELATED SUPPORTING PROTOCOLS

- [INTERACTIVE CONNECTIVITY ESTABLISHMENT (ICE): A PROTOCOL FOR NETWORK ADDRESS TRANSLATOR(NAT) FOR OFFER/ANSWER PROTOCOL](https://tools.ietf.org/html/rfc5245)
- [SESSION TRAVERSAL UTILITIES FOR NAT (STUN)](https://tools.ietf.org/html/rfc5389)
- [URI SCHEME FOR THE SESSION TRAVERSAL UTILITIES FOR NAT (STUN) PROTOCOL](https://tools.ietf.org/html/rfc7064)
- [TRAVERSAL USING RELAYS AROUND NAT (TURN) UNIFORM RESOURCE IDENTIFIES](https://tools.ietf.org/html/rfc7065)
- [AN OFFER/ANSWER MODEL WITH SESSION DESCRIPTION PROTOCOL (SDP)](https://tools.ietf.org/html/rfc3264)
- [SESSION TRAVERSAL UTILITIES FOR NAT (STUN) EXTENSION FOR THIRD PARTY AUTHORIZATION](https://datatracker.ietf.org/doc/draft-ietf-tram-turn-third-party-authz/)

#### WEBRTC STATISTICS

- [WEBRTC STATISTICS API](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_Statistics_API)

## __SPECIFICATIONS__

- [WEBRTC 1.0: REAL TIME COMMUNICATION BETWEEN BROWSERS](https://w3c.github.io/webrtc-pc/)
- [MEDIA CAPTURE AND STREAMS](https://w3c.github.io/mediacapture-main/)
- [MEDIA CAPTURE FROM DOM ELEMENTS](https://w3c.github.io/mediacapture-fromelement/)

In additions to these specifications defining the API needed to use WebRTC, there are several protocols, listed under resources.

## __SEE ALSO__

- [MediaDevices](https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices)
- [MediaStreamEvent](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamEvent)
- [MediaStreamConstraints](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamConstraints)
- [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)
- [MessageEvent](https://developer.mozilla.org/en-US/docs/Web/API/MessageEvent)
- [MediaStream](https://developer.mozilla.org/en-US/docs/Web/API/MediaStream)
- [Media Caputer and Stream API (Media Stream)](https://developer.mozilla.org/en-US/docs/Web/API/Media_Streams_API)
- [Firefox multistream and renegotiation of Jitsi Videobridge](https://hacks.mozilla.org/2015/06/firefox-multistream-and-renegotiation-for-jitsi-videobridge/)
- [Peering Through the WebRTC Fog with SocketPeer](https://hacks.mozilla.org/2015/04/peering-through-the-webrtc-fog-with-socketpeer/)
- [Inside the Party Bus: Building a Web App with Multiple Live Video Streams + Interactive Grphics](https://hacks.mozilla.org/2014/04/inside-the-party-bus-building-a-web-app-with-multiple-live-video-streams-interactive-graphics/)
- [Web media technologies](https://developer.mozilla.org/en-US/docs/Web/Media)

