/**
 * 
 */
import React, { Component } from 'react';

import Paragraph from '../components/paragraph';
import Header from '../components/header';
import Collapse from '../components/collapse';
import Hyperlink from '../components/hyperlink';
import Button from '../components/button';
import Card from '../components/card';
import Navigation from '../components/navigation';
import Dropdown from '../components/dropdown';
import Divider from '../components/divider';
import Form from '../components/form';
import Input from '../components/input';
import NavigationBar from '../components/navigation/bar';
import Toggle from '../components/button/toggle';
import Text from '../components/text';
import Context from '../context';

import Contextual from '../contextual';

export default class ExampleCollapseView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">

                    <div style={{padding: '5px'}}>
                        <Paragraph>
                            <Hyperlink role="button"
                            data-bs-toggle="collapse"
                            href="#collapseExample14"
                            aria-expanded="false"
                            aria-controls="collapseExample14" contextual={Contextual.primary}>Link with href</Hyperlink>
                            <Button data-bs-toggle="collapse" data-bs-target="#collapseExample14" aria-expanded="false" aria-controls="collapseExample14" contextual={Contextual.primary}>Button with data-bs-target</Button>
                        </Paragraph>
                        <Collapse id="collapseExample14" onShow={event=>console.log('show', event)}
                                                        onShown={event=>console.log('shown', event)}
                                                        onHide={event=>console.log('hide', event)}
                                                        onHidden={event=>console.log('hidden', event)}>
                            <Card className="card-body">
                                Anim pariatur cliche reprehenderit, enim eiusmod high life accusamus terry richardson ad squid. Nihil anim keffiyeh helvetica, craft beer labore wes anderson cred nesciunt sapiente ea proident.
                            </Card>
                        </Collapse>
                    </div>
                    {/** COLLAPSE: MULTIPLE */}
                    <div style={{padding: '5px'}}>
                        <Paragraph>
                            <Hyperlink role="button" data-bs-toggle="collapse" href="#collapseExample11" aria-expanded="false" aria-controls="collapseExample11" contextual={Contextual.primary}>Link with href</Hyperlink>
                            <Button data-bs-toggle="collapse" data-bs-target="#collapseExample12" aria-expanded="false" aria-controls="collapseExample11" contextual={Contextual.primary}>Button with data-bs-target</Button>
                            <Button data-bs-toggle="collapse" data-bs-target=".multi-collapse" aria-expanded="false" aria-controls="collapseExample11" contextual={Contextual.primary}>Both</Button>
                        </Paragraph>
                        <div className="row">
                            <div className="col">
                                <Collapse id="collapseExample11" multi>
                                    <Card className="card-body">
                                        Anim pariatur cliche reprehenderit, enim eiusmod high life accusamus terry richardson ad squid. Nihil anim keffiyeh helvetica, craft beer labore wes anderson cred nesciunt sapiente ea proident.
                                    </Card>
                                </Collapse>
                            </div>
                            <div className="col">
                                <Collapse id="collapseExample12" multi>
                                    <Card className="card-body">
                                        Anim pariatur cliche reprehenderit, enim eiusmod high life accusamus terry richardson ad squid. Nihil anim keffiyeh helvetica, craft beer labore wes anderson cred nesciunt sapiente ea proident.
                                    </Card>
                                </Collapse>
                            </div>
                        </div>
                    </div>
                    {/** COLLAPSE */}
                    <div style={{padding: '5px'}}>
                        <Paragraph>
                            <Hyperlink role="button"
                            data-bs-toggle="collapse"
                            href="#collapseExample10"
                            aria-expanded="false"
                            aria-controls="collapseExample10" contextual={Contextual.primary}>Link with href</Hyperlink>
                            <Button data-bs-toggle="collapse" data-bs-target="#collapseExample10" aria-expanded="false" aria-controls="collapseExample10" contextual={Contextual.primary}>Button with data-bs-target</Button>
                        </Paragraph>
                        <Collapse id="collapseExample10">
                            <Card className="card-body">
                                Anim pariatur cliche reprehenderit, enim eiusmod high life accusamus terry richardson ad squid. Nihil anim keffiyeh helvetica, craft beer labore wes anderson cred nesciunt sapiente ea proident.
                            </Card>
                        </Collapse>
                    </div>

                    
                    
                    
                    {/** EXTENRAL */}
                    <div style={{padding: '5px'}}>
                        <Collapse id="navbarSupportedContent6" className="bg-dark p-4" >
                            <Header size={5} className="text-white h4">Collapsed content</Header>
                            <Text className="text-muted">
                                Toggleable via the navbar brand.
                            </Text>
                            <Navigation className="me-auto mb-2 mb-lg-0">
                                <Hyperlink active>Home</Hyperlink>
                                <Hyperlink>Link</Hyperlink>
                                <Dropdown type="link" name="Dropdown button" id="navbarDropdown" expanded={false}>
                                    <Hyperlink>Action</Hyperlink>
                                    <Hyperlink>Another action</Hyperlink>
                                    <Hyperlink>Something else here</Hyperlink>
                                    <Divider />
                                    <Hyperlink>Separated link</Hyperlink>
                                </Dropdown>
                                <Hyperlink disabled>Disabled</Hyperlink>
                            </Navigation>
                            <Form className="d-flex">
                                <Input type="search" placeholder="Search" label="Search" className="me-2" />
                                <Button type="submit" outline contextual={Contextual.success}>Search</Button>
                            </Form>
                        </Collapse>
                        <NavigationBar contextual={Contextual.dark}>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent6">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                        </NavigationBar>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}