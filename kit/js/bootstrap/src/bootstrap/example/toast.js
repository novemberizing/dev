/**
 * TODO: TOAST 가 종료되지 않는다.
 */

import React, { Component } from 'react';

import Toast from '../components/toast';
import Header from '../components/header';
import Body from '../components/body';
import Button from '../components/button';
import Context from '../context';

import Contextual from '../contextual';

export default class ExampleToastView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** TOAST: COLOR SCHEMES */}
                    <div style={{padding: '5px'}}>

                        <Toast className="fade show d-flex align-item-center text-white border-0" color={Contextual.primary}
                            onShow={event => console.log('show', event)}
                            onShown={event => console.log('shown', event)}
                            onHide={event => console.log('hide', event)}
                            onHidden={event => console.log('hidden', event)}>
                            <Button type="close" data-bs-dismiss="toast" className="ms-auto me-2" white></Button>
                            <Body>
                                Hello, world! This is a toast message.
                                <Button type="close" data-bs-dismiss="toast" className="ms-auto me-2" white></Button>
                            </Body>
                            <Button type="close" data-bs-dismiss="toast" className="ms-auto me-2" white></Button>
                        </Toast>
                    </div>
                    {/** TOAST: PLACEMENT: TODO */}
                    <div style={{padding: '5px'}}>
                        <form>
                            <div className="form-group mb-3">
                                <label htmlFor="selectToastPlacement">Toast placement</label>
                                <select className="form-select mt-2" id="selectToastPlacement">
                                    <option value="" defaultValue>Select a position...</option>
                                    <option value="top-0 start-0">Top left</option>
                                    <option value="top-0 start-50 translate-middle-x">Top center</option>
                                    <option value="top-0 end-0">Top right</option>
                                    <option value="top-50 start-0 translate-middle-y">Middle left</option>
                                    <option value="top-50 start-50 translate-middle">Middle center</option>
                                    <option value="top-50 end-0 translate-middle-y">Middle right</option>
                                    <option value="bottom-0 start-0">Bottom left</option>
                                    <option value="bottom-0 start-50 translate-middle-x">Bottom center</option>
                                    <option value="bottom-0 end-0">Bottom right</option>
                                </select>
                            </div>
                            <div aria-live="polite" aria-atomic="true" className="bg-dark position-relative bd-example-toasts"  style={{minHeight: '240px'}}>
                                <div className="toast-container position-absolute p-3" id="toastPlacement">
                                    <Toast className="fade show">
                                        <Header>
                                            <svg className="bd-placeholder-img rounded me-2" width="20" height="20" xmlns="http://www.w3.org/2000/svg" aria-hidden="true" preserveAspectRatio="xMidYMid slice" focusable="false"><rect width="100%" height="100%" fill="#007aff"></rect></svg>
                                            <strong className="me-auto">Bootstrap</strong>
                                            <small>11 mins ago</small>
                                            <Button type="close" data-bs-dismiss="toast"></Button>
                                        </Header>
                                        <Body>
                                            Hello, world! This is a toast message.
                                        </Body>
                                    </Toast>
                                </div>
                            </div>
                        </form>
                    </div>
                    {/** TOAST: COLOR SCHEMES */}
                    <div style={{padding: '5px'}}>
                    <Toast className="fade show d-flex align-item-center text-white border-0" color={Contextual.primary}>
                        <Body>
                            Hello, world! This is a toast message.
                        </Body>
                        <Button type="close" data-bs-dismiss="toast" className="ms-auto me-2" white></Button>
                    </Toast>
                    </div>
                    {/** TOAST: CUSTOM CONTENT */}
                    <div style={{padding: '5px'}}>
                    <Toast className="fade show">
                        <Body>
                            Hello, world! This is a toast message.
                            <div className="mt-2 pt-2 border-top">
                                <Button contextual={Contextual.primary} size={Button.sm}>Take action</Button>
                                <Button data-bs-dismiss="toast" className="ms-auto me-2" size={Button.sm}>Close</Button>
                            </div>
                        </Body>
                    </Toast>
                    </div>
                    <div style={{padding: '5px'}}>
                    <Toast className="fade show d-flex align-item-center">
                        <Body>
                            Hello, world! This is a toast message.
                        </Body>
                        <Button type="close" data-bs-dismiss="toast" className="ms-auto me-2"></Button>
                    </Toast>
                    </div>
                    {/** TOAST: STACKING */}
                    <div style={{padding: '5px'}}>
                    <div className="toast-container">
                        <Toast className="fade show">
                            <Header>
                                <svg className="bd-placeholder-img rounded me-2" width="20" height="20" xmlns="http://www.w3.org/2000/svg" aria-hidden="true" preserveAspectRatio="xMidYMid slice" focusable="false"><rect width="100%" height="100%" fill="#007aff"></rect></svg>
                                <strong className="me-auto">Bootstrap</strong>
                                <small>11 mins ago</small>
                                <Button type="close" data-bs-dismiss="toast"></Button>
                            </Header>
                            <Body>
                                Hello, world! This is a toast message.
                            </Body>
                        </Toast>
                        <Toast className="fade show">
                            <Header>
                                <svg className="bd-placeholder-img rounded me-2" width="20" height="20" xmlns="http://www.w3.org/2000/svg" aria-hidden="true" preserveAspectRatio="xMidYMid slice" focusable="false"><rect width="100%" height="100%" fill="#007aff"></rect></svg>
                                <strong className="me-auto">Bootstrap</strong>
                                <small>11 mins ago</small>
                                <Button type="close" data-bs-dismiss="toast"></Button>
                            </Header>
                            <Body>
                                Hello, world! This is a toast message.
                            </Body>
                        </Toast>
                    </div>
                    </div>
                    {/** TOAST: TRANSLUCENT */}
                    <div style={{padding: '5px'}} className="bg-dark">
                    <Toast className="fade show">
                        <Header>
                            <svg className="bd-placeholder-img rounded me-2" width="20" height="20" xmlns="http://www.w3.org/2000/svg" aria-hidden="true" preserveAspectRatio="xMidYMid slice" focusable="false"><rect width="100%" height="100%" fill="#007aff"></rect></svg>
                            <strong className="me-auto">Bootstrap</strong>
                            <small>11 mins ago</small>
                            <Button type="close" data-bs-dismiss="toast"></Button>
                        </Header>
                        <Body>
                            Hello, world! This is a toast message.
                        </Body>
                    </Toast>
                    </div>
                    {/** TOAST */}
                    <div style={{padding: '5px'}}>
                    <Toast className="fade show">
                        <Header>
                            <svg className="bd-placeholder-img rounded me-2" width="20" height="20" xmlns="http://www.w3.org/2000/svg" aria-hidden="true" preserveAspectRatio="xMidYMid slice" focusable="false"><rect width="100%" height="100%" fill="#007aff"></rect></svg>
                            <strong className="me-auto">Bootstrap</strong>
                            <small>11 mins ago</small>
                            <Button type="close" data-bs-dismiss="toast"></Button>
                        </Header>
                        <Body>
                            Hello, world! This is a toast message.
                        </Body>
                    </Toast>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}