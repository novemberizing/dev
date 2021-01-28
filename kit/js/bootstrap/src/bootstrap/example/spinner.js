import React, { Component } from 'react';

import Button from '../components/button';
import Spinner from '../components/spinner';

import Contextual from '../contextual';
import Context from '../context';

export default class ExampleSpinnerView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** SPINNER: BUTTON */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} disabled>
                            <Spinner label="Loading..." size={Spinner.sm} className="me-2" grow aria-hidden="true"></Spinner>
                        </Button>
                        <Button contextual={Contextual.primary} disabled>
                            <Spinner label="Loading..." size={Spinner.sm} className="me-2" grow aria-hidden="true"></Spinner>
                            Loading...
                        </Button>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} disabled>
                            <Spinner label="Loading..." size={Spinner.sm} className="me-2" aria-hidden="true"></Spinner>
                        </Button>
                        <Button contextual={Contextual.primary} disabled>
                            <Spinner label="Loading..." size={Spinner.sm} className="me-2" aria-hidden="true"></Spinner>
                            Loading...
                        </Button>
                    </div>
                    {/** SPINNER: SIZE */}
                    <div style={{padding: '5px'}}>
                        <Spinner label="Loading..." size={Spinner.sm}></Spinner>
                        <Spinner label="Loading..." size={Spinner.sm} grow></Spinner>
                        <Spinner label="Loading..." size={Spinner.lg}></Spinner>
                        <Spinner label="Loading..." size={Spinner.lg} grow></Spinner>
                        <Spinner label="Loading..." style={{width: '3rem', height: '3rem'}}></Spinner>
                        <Spinner label="Loading..." style={{width: '3rem', height: '3rem'}} grow></Spinner>
                    </div>
                    {/** SPINNER: TEXT ALIGN */}
                    <div style={{padding: '5px'}}>
                        <div className="text-center">
                            <Spinner label="Loading..."></Spinner>
                        </div>
                    </div>
                    {/** SPINNER: FLOATS */}
                    <div style={{padding: '5px'}}>
                        <div className="clearfix">
                            <Spinner label="Loading..." className="float-end"></Spinner>
                        </div>
                    </div>
                    {/** SPINNER: PLACEMENT */}
                    <div style={{padding: '5px'}}>
                        <div className="d-flex justify-content-center">
                            <strong>Loading...</strong>
                            <Spinner label="Loading..." className="ms-auto"></Spinner>
                        </div>
                    </div>
                    <div style={{padding: '5px'}}>
                        <div className="d-flex justify-content-center">
                            <Spinner label="Loading..."></Spinner>
                        </div>
                    </div>
                    {/** SPINNER: ALIGNMENT */}
                    <div style={{padding: '5px'}}>
                        <Spinner label="Loading..." className="m-5"></Spinner>
                    </div>
                    {/** SPINNER: GLOW */}
                    <div style={{padding: '5px'}}>
                        <Spinner label="Loading..." color={Contextual.primary} grow></Spinner>
                        <Spinner label="Loading..." color={Contextual.secondary} grow></Spinner>
                        <Spinner label="Loading..." color={Contextual.danger} grow></Spinner>
                        <Spinner label="Loading..." color={Contextual.success} grow></Spinner>
                        <Spinner label="Loading..." color={Contextual.warning} grow></Spinner>
                        <Spinner label="Loading..." color={Contextual.info} grow></Spinner>
                        <Spinner label="Loading..." color={Contextual.light} grow></Spinner>
                        <Spinner label="Loading..." color={Contextual.dark} grow></Spinner>
                    </div>
                    {/** SPINNER: COLOR */}
                    <div style={{padding: '5px'}}>
                        <Spinner label="Loading..." color={Contextual.primary}></Spinner>
                        <Spinner label="Loading..." color={Contextual.secondary}></Spinner>
                        <Spinner label="Loading..." color={Contextual.danger}></Spinner>
                        <Spinner label="Loading..." color={Contextual.success}></Spinner>
                        <Spinner label="Loading..." color={Contextual.warning}></Spinner>
                        <Spinner label="Loading..." color={Contextual.info}></Spinner>
                        <Spinner label="Loading..." color={Contextual.light}></Spinner>
                        <Spinner label="Loading..." color={Contextual.dark}></Spinner>
                    </div>
                    {/** SPINNER */}
                    <div style={{padding: '5px'}}>
                        <Spinner label="Loading..."></Spinner>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}