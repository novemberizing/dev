/**
 * 
 */
import React, { Component } from 'react';

import Tooltip from '../components/tooltip';
import Context from '../context';

import Contextual from '../contextual';

export default class ExampleTooltipView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    <div style={{padding: '5px', margin: '50px'}}>
                        <Tooltip contextual={Contextual.secondary}
                                title="<em>Tooltip</em> <u>with</u> <b>HTML</b>"
                                placement="bottom"
                                html
                                onShow={event => console.log('show', event)}
                                onShown={event => console.log('shown', event)}
                                onHide={event => console.log('hide', event)}
                                onHidden={event => console.log('hidden', event)}
                                onInserted={event => console.log('inserted', event)}>Tooltip on HTML</Tooltip>
                    </div>
                    <div style={{padding: '5px', margin: '50px'}}>
                        <Tooltip contextual={Contextual.secondary} title="<em>Tooltip</em> <u>with</u> <b>HTML</b>" placement="bottom" html>Tooltip on HTML</Tooltip>
                        <Tooltip contextual={Contextual.secondary} title="title" placement="top">Tooltip on Top</Tooltip>
                        <Tooltip contextual={Contextual.secondary} title="title" placement="bottom">Tooltip on Bottom</Tooltip>
                        <Tooltip contextual={Contextual.secondary} title="title" placement="right">Tooltip on Right</Tooltip>
                        <Tooltip contextual={Contextual.secondary} title="title" placement="left">Tooltip on Left</Tooltip>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}