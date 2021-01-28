/**
 * 
 */
import React, { Component } from 'react';

import Breadcrumb from '../components/breadcrumb';
import BreadcrumbItem from '../components/breadcrumb/item';
import Context from '../context';

export default class ExampleBreadcrumbView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** BREADCRUMB: DIVIDER */}
                    <div style={{padding: '5px'}}>
                        <Breadcrumb divider=''>
                            <BreadcrumbItem href="#home">Home</BreadcrumbItem>
                            <BreadcrumbItem href="#library">Library</BreadcrumbItem>
                            <BreadcrumbItem href='#data'>Data</BreadcrumbItem>
                        </Breadcrumb>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Breadcrumb divider='>'>
                            <BreadcrumbItem href="#home">Home</BreadcrumbItem>
                            <BreadcrumbItem href="#library">Library</BreadcrumbItem>
                            <BreadcrumbItem href='#data'>Data</BreadcrumbItem>
                        </Breadcrumb>
                    </div>
                    {/** BREADCRUMB */}
                    <div style={{padding: '5px'}}>
                        <Breadcrumb>
                            <BreadcrumbItem href="#home">Home</BreadcrumbItem>
                            <BreadcrumbItem href="#library">Library</BreadcrumbItem>
                            <BreadcrumbItem href='#data'>Data</BreadcrumbItem>
                        </Breadcrumb>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Breadcrumb>
                            <BreadcrumbItem>Home</BreadcrumbItem>
                            <BreadcrumbItem>Library</BreadcrumbItem>
                        </Breadcrumb>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Breadcrumb>
                            <BreadcrumbItem>Home</BreadcrumbItem>
                        </Breadcrumb>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}