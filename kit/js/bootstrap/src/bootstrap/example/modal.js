/**
 * 
 */
import React, { Component } from 'react';

import Button from '../components/button';
import Content from '../components/content';
import Header from '../components/header';
import Title from '../components/title';
import Footer from '../components/footer';
import Body from '../components/body';
import Modal from '../components/modal';
import Paragraph from '../components/paragraph';
import Context from '../context';

import Breakpoint from '../breakpoint';
import Contextual from '../contextual';

export default class ExampleModalView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** MODAL: FULLSCREEN */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#exampleModalA11" toggle="modal" data-bs-whatever="@mdo">FULLSCREEN XXL</Button>
                        <Modal id="exampleModalA11" aria-labelledby="exampleModalA11Label" aria-hidden="true" fade backdrop="static" size={Modal.sm} fullscreen={Breakpoint.xxl}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA11Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                        <Button contextual={Contextual.primary} target="#exampleModalA10" toggle="modal" data-bs-whatever="@mdo">FULLSCREEN XL</Button>
                        <Modal id="exampleModalA10" aria-labelledby="exampleModalA10Label" aria-hidden="true" fade backdrop="static" size={Modal.sm} fullscreen={Breakpoint.xl}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA10Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                        <Button contextual={Contextual.primary} target="#exampleModalA9" toggle="modal" data-bs-whatever="@mdo">FULLSCREEN LG</Button>
                        <Modal id="exampleModalA9" aria-labelledby="exampleModalA9Label" aria-hidden="true" fade backdrop="static" size={Modal.sm} fullscreen={Breakpoint.lg}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA9Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                        <Button contextual={Contextual.primary} target="#exampleModalA8" toggle="modal" data-bs-whatever="@mdo">FULLSCREEN MD</Button>
                        <Modal id="exampleModalA8" aria-labelledby="exampleModalA8Label" aria-hidden="true" fade backdrop="static" size={Modal.sm} fullscreen={Breakpoint.md}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA8Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                        <Button contextual={Contextual.primary} target="#exampleModalA7" toggle="modal" data-bs-whatever="@mdo">FULLSCREEN SM</Button>
                        <Modal id="exampleModalA7" aria-labelledby="exampleModalA7Label" aria-hidden="true" fade backdrop="static" size={Modal.sm} fullscreen={Breakpoint.sm}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA7Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                        <Button contextual={Contextual.primary} target="#exampleModalA6" toggle="modal" data-bs-whatever="@mdo">FULLSCREEN</Button>
                        <Modal id="exampleModalA6" aria-labelledby="exampleModalA6Label" aria-hidden="true" fade backdrop="static" size={Modal.sm} fullscreen>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA6Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    {/** MODAL: SIZE */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#exampleModalA5" toggle="modal" data-bs-whatever="@mdo">Extra large modal</Button>
                        <Modal id="exampleModalA5" aria-labelledby="exampleModalA5Label" aria-hidden="true" fade backdrop="static" size={Modal.sm}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA5Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#exampleModalA4" toggle="modal" data-bs-whatever="@mdo">Extra large modal</Button>
                        <Modal id="exampleModalA4" aria-labelledby="exampleModalA4Label" aria-hidden="true" fade backdrop="static" size={Modal.lg}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA4Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#exampleModalA3" toggle="modal" data-bs-whatever="@mdo">Extra large modal</Button>
                        <Modal id="exampleModalA3" aria-labelledby="exampleModalA3Label" aria-hidden="true" fade backdrop="static" size={Modal.xl}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA3Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    {/** MODAL: VARYING CONTENT: NEED TO ADD EVENT HANDLING */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#exampleModalA2" toggle="modal" data-bs-whatever="@mdo">Open modal for @mdo</Button>
                        <Button contextual={Contextual.primary} target="#exampleModalA2" toggle="modal" data-bs-whatever="@fat">Open modal for @fat</Button>
                        <Button contextual={Contextual.primary} target="#exampleModalA2" toggle="modal" data-bs-whatever="@getbootstrap">Open modal for @getbootstrap</Button>
                        <Modal id="exampleModalA2" aria-labelledby="exampleModalA2Label" aria-hidden="true" fade backdrop="static" keyboard={false} centered
                            onShow={event => console.log('show', event, event.relatedTarget.getAttribute('data-bs-whatever'))}
                            onShown={event => console.log('shown', event, event.relatedTarget.getAttribute('data-bs-whatever'))}
                            onHide={event => console.log('hide', event)}
                            onHidden={event => console.log('hidden', event)}
                            onHidePrevented={event => console.log('hide prevented', event)}>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA2Label" size={5}>New message</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <form>
                                        <div className="mb-3">
                                            <label htmlFor="recipient-name" className="col-form-label">Recipient:</label>
                                            <input type="text" className="form-control" id="recipient-name" />
                                        </div>
                                        <div className="mb-3">
                                            <label htmlFor="message-text" className="col-form-label">Message:</label>
                                            <textarea className="form-control" id="message-text"></textarea>
                                        </div>
                                    </form>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>   
                        

                    </div>
                    {/** MODAL: GRID */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#exampleModalA1" toggle="modal">Launch grid modal</Button>
                        <Modal id="exampleModalA1" aria-labelledby="exampleModalA1Label" aria-hidden="true" fade backdrop="static" keyboard={false} centered>
                            <Content>
                                <Header>
                                    <Title id="exampleModalA1Label" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <div className="container-fluid">
                                        <div className="row">
                                            <div className="col-md-4">.col-md-4</div>
                                            <div className="col-md-4 ms-auto">.col-md-4 .ms-auto</div>
                                        </div>
                                        <div className="row">
                                            <div className="col-md-3 ms-auto">.col-md-3 .ms-auto</div>
                                            <div className="col-md-2 ms-auto">.col-md-2 .ms-auto</div>
                                        </div>
                                        <div className="row">
                                            <div className="col-md-6 ms-auto">.col-md-6 .ms-auto</div>
                                        </div>
                                        <div className="row">
                                            <div className="col-sm-9">
                                                Level 1: .col-sm-9
                                                <div className="row">
                                                    <div className="col-8 col-sm-6">
                                                        Level 2: .col-8 .col-sm-6
                                                    </div>
                                                    <div className="col-4 col-sm-6">
                                                        Level 2: .col-4 .col-sm-6
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>                    
                    </div>
                    {/** MODAL: CENTERED */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#staticBackdrop1" toggle="modal">Launch static backdrop modal</Button>
                        <Modal id="staticBackdrop1" aria-labelledby="staticBackdropLabel1" aria-hidden="true" fade backdrop="static" keyboard={false} centered>
                            <Content>
                                <Header>
                                    <Title id="staticBackdropLabel1" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#longContent3" toggle="modal">Launch static backdrop modal</Button>
                        <Modal id="longContent3" aria-labelledby="longContentLabel3" aria-hidden="true" fade backdrop="static" keyboard={false} scrollable centered>
                            <Content>
                                <Header>
                                    <Title id="longContentLabel3" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    {/** MODAL: LONG CONTENT */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#longContent2" toggle="modal">Launch static backdrop modal</Button>
                        <Modal id="longContent2" aria-labelledby="longContentLabel2" aria-hidden="true" fade backdrop="static" keyboard={false} scrollable>
                            <Content>
                                <Header>
                                    <Title id="longContentLabel2" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    {/** MODAL: LONG CONTENT */}
                    <div style={{padding: '5px'}}>
                    <Button contextual={Contextual.primary} target="#longContent" toggle="modal">Launch static backdrop modal</Button>
                        <Modal id="longContent" aria-labelledby="longContentLabel" aria-hidden="true" fade backdrop="static" keyboard={false}>
                            <Content>
                                <Header>
                                    <Title id="longContentLabel" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                    <Paragraph>Cras mattis consectetur purus sit amet fermentum. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</Paragraph>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor.</Paragraph>
                                    <Paragraph>Aenean lacinia bibendum nulla sed consectetur. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Donec sed odio dui. Donec ullamcorper nulla non metus auctor fringilla.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    {/** MODAL: STATIC BACKDROP */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#staticBackdrop" toggle="modal">Launch static backdrop modal</Button>
                        <Modal id="staticBackdrop" aria-labelledby="staticBackdropLabel" aria-hidden="true" fade backdrop="static" keyboard={false}>
                            <Content>
                                <Header>
                                    <Title id="staticBackdropLabel" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Understood</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    {/** MODAL LIVE DEMO */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} target="#exampleModal" toggle="modal">Launch demo modal</Button>
                        <Modal id="exampleModal" aria-labelledby="exampleModalLabel" aria-hidden="true" fade>
                            <Content>
                                <Header>
                                    <Title id="exampleModalLabel" size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Save changes</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                    {/** MODAL */}
                    <div style={{padding: '5px'}}>
                        <Modal style={{display: 'block', position: 'static'}}>
                            <Content>
                                <Header>
                                    <Title size={5}>Modal title</Title>
                                    <Button type="close" dismiss></Button>
                                </Header>
                                <Body>
                                    <Paragraph>Modal body text goes here.</Paragraph>
                                </Body>
                                <Footer>
                                    <Button contextual={Contextual.secondary} dismiss>Close</Button>
                                    <Button contextual={Contextual.primary}>Save changes</Button>
                                </Footer>
                            </Content>
                        </Modal>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}