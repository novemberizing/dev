import React, { Component } from 'react';

import Progress from '../components/progress';
import ProgressBar from '../components/progress/bar';

import Contextual from '../contextual';
import Context from '../context';

export default class ExampleProgressView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** PROGRESS ANIMATED */}
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={75} contextual={Contextual.info} striped animated /></Progress>
                    </div>
                    {/** PROGRESS STRIPED */}
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={100} contextual={Contextual.success} striped /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={75} contextual={Contextual.info} striped /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={50} contextual={Contextual.warning} striped /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={25} contextual={Contextual.danger} striped /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={5} striped /></Progress>
                    </div>
                    {/** PROGRESS MULTIBAR */}
                    <div style={{padding: '5px'}}>
                        <Progress>
                                <ProgressBar now={15} />
                                <ProgressBar now={30} contextual={Contextual.success} />
                                <ProgressBar now={20} contextual={Contextual.info} />
                        </Progress>
                    </div>
                    {/** PROGRESS BACKGROUND */}
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={100} contextual={Contextual.success} /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={75} contextual={Contextual.info} /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={50} contextual={Contextual.warning} /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={25} contextual={Contextual.danger} /></Progress>
                    </div>
                    {/** PROGRESS HEIGHT */}
                    <div style={{padding: '5px'}}>
                        <Progress style={{height: '2px'}}><ProgressBar now={25}></ProgressBar></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress style={{height: '20px'}}><ProgressBar now={25}></ProgressBar></Progress>
                    </div>
                    {/** PROGRESS LABEL */}
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={25}>25%</ProgressBar></Progress>
                    </div>
                    {/** PROGRESS */}
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={100} /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={75} /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={50} /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={25} /></Progress>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Progress><ProgressBar now={0} /></Progress>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}