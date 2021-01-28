/**
 * 
 */
import React, { Component } from 'react';

import Dropdown from '../components/dropdown';
import Hyperlink from '../components/hyperlink';
import Divider from '../components/dropdown';
import ButtonGroup from '../components/button/group';
import Context from '../context';

import Contextual from '../contextual';

export default class ExampleDropdownView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** DROPDOWN DARK */}
                    <div style={{padding: '5px'}}>
                        <Dropdown name="Primary" contextual={Contextual.secondary} id="dropdownMenuButton1" expanded={false} size={Dropdown.sm} dark>
                            <Hyperlink active>Action</Hyperlink>
                            <Hyperlink>Another action</Hyperlink>
                            <Hyperlink>Something else here</Hyperlink>
                            <Divider />
                            <Hyperlink>Separated link</Hyperlink>
                        </Dropdown>
                    </div>
                    {/** DROPDOWN SIZE: SMALL */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup>
                            <Dropdown name="Primary" contextual={Contextual.secondary} id="dropdownMenuButton1" expanded={false} size={Dropdown.sm} >
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Secondary" contextual={Contextual.secondary} id="dropdownMenuButton2" expanded={false} size={Dropdown.sm} split>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                        </ButtonGroup>
                    </div>
                    {/** DROPDOWN SIZE: LG */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup>
                            <Dropdown name="Primary" contextual={Contextual.secondary} id="dropdownMenuButton1" expanded={false} size={Dropdown.lg} >
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Secondary" contextual={Contextual.secondary} id="dropdownMenuButton2" expanded={false} size={Dropdown.lg} split>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                        </ButtonGroup>
                    </div>
                    {/** DROPDOWN STYLE: SPLIT */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup>
                            <Dropdown name="Primary" contextual={Contextual.primary} id="dropdownMenuButton" expanded={false} split>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Secondary" contextual={Contextual.secondary} id="dropdownMenuButton" expanded={false} split>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Success" contextual={Contextual.success} id="dropdownMenuButton" expanded={false} split>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Info" contextual={Contextual.info} id="dropdownMenuButton" expanded={false} split>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Warning" contextual={Contextual.warning} id="dropdownMenuButton" expanded={false} split>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Danger" contextual={Contextual.danger} id="dropdownMenuButton" expanded={false} split>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                        </ButtonGroup>
                    </div>
                    {/** DROPDOWN STYLE */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup>
                            <Dropdown name="Primary" contextual={Contextual.primary} id="dropdownMenuButton" expanded={false}>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Secondary" contextual={Contextual.secondary} id="dropdownMenuButton" expanded={false}>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Success" contextual={Contextual.success} id="dropdownMenuButton" expanded={false}>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Info" contextual={Contextual.info} id="dropdownMenuButton" expanded={false}>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Warning" contextual={Contextual.warning} id="dropdownMenuButton" expanded={false}>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Dropdown name="Danger" contextual={Contextual.danger} id="dropdownMenuButton" expanded={false}>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                        </ButtonGroup>
                    </div>
                    {/** DROPDOWN */}
                    <div style={{padding: '5px'}}>
                        <Dropdown name="Dropdown button" contextual={Contextual.secondary} id="dropdownMenuButton" expanded={false}>
                            <Hyperlink>Action</Hyperlink>
                            <Hyperlink>Another action</Hyperlink>
                            <Hyperlink>Something else here</Hyperlink>
                        </Dropdown>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}