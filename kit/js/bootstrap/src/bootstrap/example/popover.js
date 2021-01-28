/**
 * 
 */
import React, { Component } from 'react';

import Popover from '../components/popover';
import Contextual from '../contextual';
import Context from '../context';

export default class ExamplePopoverView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** POPOVER: EVENT */}
                    <div style={{padding: '5px'}}>
                        <Popover contextual={Contextual.danger}
                                size={Popover.lg}
                                title="Popover title"
                                onShow={event => console.log('show', event)}
                                onShown={event => console.log('shown', event)}
                                onHide={event => console.log('hide', event)}
                                onHidden={event => console.log('hidden', event)}
                                onInserted={event => console.log('inserted', event)}
                                content="And here's some amazing content. It's very engaging. Right?">
                            Click to toggle popover
                        </Popover>
                    </div>
                    {/** POPOVER: DISABLE */}
                    <div style={{padding: '5px'}}>
                        <Popover contextual={Contextual.danger}
                                size={Popover.lg}
                                title="Popover title"
                                disabled
                                content="And here's some amazing content. It's very engaging. Right?">
                            Click to toggle popover
                        </Popover>
                    </div>
                    {/** POPOVER: DISMISS ON CLICK */}
                    <div style={{padding: '5px'}}>
                        <Popover contextual={Contextual.danger}
                                size={Popover.lg}
                                title="Popover title"
                                content="And here's some amazing content. It's very engaging. Right?">
                            Click to toggle popover
                        </Popover>
                    </div>
                    {/** POPOVER: DIRECTION */}
                    <div style={{padding: '5px', marginTop: '150px'}}>
                        <Popover contextual={Contextual.danger}
                                container="body"
                                placement="top"
                                content="And here's some amazing content. It's very engaging. Right?">
                            Click to toggle popover (Top)
                        </Popover>
                        <Popover contextual={Contextual.danger}
                                container="body"
                                placement="right"
                                content="And here's some amazing content. It's very engaging. Right?">
                            Click to toggle popover (Right)
                        </Popover>
                        <Popover contextual={Contextual.danger}
                                container="body"
                                placement="left"
                                content="And here's some amazing content. It's very engaging. Right?">
                            Click to toggle popover (Left)
                        </Popover>
                        <Popover contextual={Contextual.danger}
                                container="body"
                                placement="bottom"
                                content="And here's some amazing content. It's very engaging. Right?">
                            Click to toggle popover (Bottom)
                        </Popover>
                    </div>
                    {/** POPOVER */}
                    <div style={{padding: '5px'}}>
                        <Popover contextual={Contextual.danger}
                                size={Popover.lg}
                                title="Popover title"
                                content="And here's some amazing content. It's very engaging. Right?">
                            Click to toggle popover
                        </Popover>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}