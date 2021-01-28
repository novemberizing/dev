/**
 * 
 */
import React, { Component } from 'react';

import Alert from '../components/alert';
import Hyperlink from '../components/hyperlink';
import Header from '../components/header';
import Paragraph from '../components/paragraph';

import Contextual from '../contextual';
import Context from '../context';

export default class ExampleAlertView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** ALERT: DISMISS */}
                    <div style={{padding: '5px'}}>
                        <Alert contextual={Contextual.warning} dismissible>
                            <strong>Holy guacamole!</strong> You should check in on some of those fields below.
                        </Alert>
                    </div>
                    {/** ALERT: ADDITIONAL CONTENT */}
                    <div style={{padding: '5px'}}>
                        <Alert contextual={Contextual.success}>
                            <Header size={4}>Well done!</Header>
                            <Paragraph>Aww yeah, you successfully read this important alert message. This example text is going to run a bit longer so that you can see how spacing within an alert works with this kind of content.</Paragraph>
                            <hr />
                            <Paragraph className="mb-0">Whenever you need to, be sure to use margin utilities to keep things nice and tidy.</Paragraph>
                        </Alert>
                    </div>
                    {/** ALERT: LINK */}
                    <div style={{padding: '5px'}}>
                        <Alert contextual={Contextual.primary}>
                            A simple primary alert with <Hyperlink>an example link</Hyperlink> Give it a click if you like.
                        </Alert>
                        <Alert contextual={Contextual.secondary}>
                            A simple secondary alert with <Hyperlink>an example link</Hyperlink> Give it a click if you like.
                        </Alert>
                        <Alert contextual={Contextual.danger}>
                            A simple danger alert with <Hyperlink>an example link</Hyperlink> Give it a click if you like.
                        </Alert>
                        <Alert contextual={Contextual.warning}>
                            A simple warning alert with <Hyperlink>an example link</Hyperlink> Give it a click if you like.
                        </Alert>
                        <Alert contextual={Contextual.info}>
                            A simple info alert with <Hyperlink>an example link</Hyperlink> Give it a click if you like.
                        </Alert>
                        <Alert contextual={Contextual.success}>
                            A simple success alert with <Hyperlink>an example link</Hyperlink> Give it a click if you like.
                        </Alert>
                        <Alert contextual={Contextual.light}>
                            A simple light alert with <Hyperlink>an example link</Hyperlink> Give it a click if you like.
                        </Alert>
                        <Alert contextual={Contextual.dark}>
                            A simple dark alert with <Hyperlink>an example link</Hyperlink> Give it a click if you like.
                        </Alert>
                    </div>
                    {/** ALERT */}
                    <div style={{padding: '5px'}}>
                        <Alert contextual={Contextual.primary}>A simple primary alert—check it out!</Alert>
                        <Alert contextual={Contextual.secondary}>A simple secondary alert—check it out!</Alert>
                        <Alert contextual={Contextual.danger}>A simple danger alert—check it out!</Alert>
                        <Alert contextual={Contextual.warning}>A simple warning alert—check it out!</Alert>
                        <Alert contextual={Contextual.success}>A simple success alert—check it out!</Alert>
                        <Alert contextual={Contextual.info}>A simple info alert—check it out!</Alert>
                        <Alert contextual={Contextual.light}>A simple light alert—check it out!</Alert>
                        <Alert contextual={Contextual.dark}>A simple dark alert—check it out!</Alert>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}