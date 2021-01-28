/**
 * 
 */
import React, { Component } from 'react';

import Badge from '../components/badge';
import Button from '../components/button';
import Header from '../components/header';

import Contextual from '../contextual';
import Context from '../context';

export default class ExampleBadgeView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** BADGE: PILL */}
                    <div style={{padding: '5px'}}>
                        <Badge contextual={Contextual.primary} pill>primary</Badge>
                        <Badge contextual={Contextual.secondary} pill>secondary</Badge>
                        <Badge contextual={Contextual.warning} className="text-dark" pill>warning</Badge>
                        <Badge contextual={Contextual.danger} pill>danger</Badge>
                        <Badge contextual={Contextual.info} className="text-dark" pill>info</Badge>
                        <Badge contextual={Contextual.success} pill>success</Badge>
                        <Badge contextual={Contextual.light} className="text-dark" pill>light</Badge>
                        <Badge contextual={Contextual.dark} pill>dark</Badge>
                    </div>
                    {/** BADGE: BACKGROUND COLOR */}
                    <div style={{padding: '5px'}}>
                        <Badge contextual={Contextual.primary}>primary</Badge>
                        <Badge contextual={Contextual.secondary}>secondary</Badge>
                        <Badge contextual={Contextual.warning} className="text-dark">warning</Badge>
                        <Badge contextual={Contextual.danger}>danger</Badge>
                        <Badge contextual={Contextual.info} className="text-dark">info</Badge>
                        <Badge contextual={Contextual.success}>success</Badge>
                        <Badge contextual={Contextual.light} className="text-dark">light</Badge>
                        <Badge contextual={Contextual.dark}>dark</Badge>
                    </div>
                    {/** BADGE */}
                    <div style={{padding: '5px'}}>
                        <Header size={1}>Example heading <Badge contextual={Contextual.secondary}>New</Badge></Header>
                        <Header size={2}>Example heading <Badge contextual={Contextual.secondary}>New</Badge></Header>
                        <Header size={3}>Example heading <Badge contextual={Contextual.secondary}>New</Badge></Header>
                        <Header size={4}>Example heading <Badge contextual={Contextual.secondary}>New</Badge></Header>
                        <Header size={5}>Example heading <Badge contextual={Contextual.secondary}>New</Badge></Header>
                        <Header size={6}>Example heading <Badge contextual={Contextual.secondary}>New</Badge></Header>
                        <Button contextual={Contextual.primary}>Notifications <Badge contextual={Contextual.secondary}>4</Badge></Button>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}