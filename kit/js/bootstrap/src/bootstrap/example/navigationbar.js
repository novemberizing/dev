/**
 * 
 */
import React, { Component } from 'react';

import NavigationBar from '../components/navigation/bar';
import Toggle from '../components/button/toggle';
import Dropdown from '../components/dropdown';
import Divider from '../components/divider';
import Collapse from '../components/collapse';
import Brand from '../components/brand';
import Navigation from '../components/navigation';
import Hyperlink from '../components/hyperlink';
import Form from '../components/form';
import Input from '../components/input';
import Button from '../components/button';
import InputGroup from '../components/input/group';
import InputText from '../components/input/text';
import Text from '../components/text';
import Context from '../context';

import Contextual from '../contextual';

import icon from '../../bootstrap-logo.svg';

export default class ExampleNavigationBarView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** HIDDEN BRAND: NAVIGATION BAR */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar expand={NavigationBar.lg} contextual={Contextual.dark}>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent5">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                            <Collapse id="navbarSupportedContent5">
                                <Brand link="type">Hidden</Brand>
                                <Navigation className="me-auto mb-2 mb-lg-0">
                                    <Hyperlink active>Home</Hyperlink>
                                    <Hyperlink>Link</Hyperlink>
                                    <Dropdown name="Dropdown button" id="navbarDropdown" expanded={false}>
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
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: COLOR */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar expand={NavigationBar.lg} contextual={Contextual.dark}>
                            <Brand type="link">Navbar</Brand>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                            <Collapse id="navbarSupportedContent">
                                <Navigation className="me-auto mb-2 mb-lg-0">
                                    <Hyperlink active>Home</Hyperlink>
                                    <Hyperlink>Link</Hyperlink>
                                    <Dropdown name="Dropdown button" id="navbarDropdown" expanded={false}>
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
                        </NavigationBar>
                    </div>
                    <div style={{padding: '5px'}}>
                        <NavigationBar expand={NavigationBar.lg} contextual={Contextual.dark} background={Contextual.primary}>
                            <Brand type="link">Navbar</Brand>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                            <Collapse id="navbarSupportedContent">
                                <Navigation className="me-auto mb-2 mb-lg-0">
                                    <Hyperlink active>Home</Hyperlink>
                                    <Hyperlink>Link</Hyperlink>
                                    <Dropdown name="Dropdown button" id="navbarDropdown" expanded={false}>
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
                        </NavigationBar>
                    </div>
                    <div style={{padding: '5px'}}>
                        <NavigationBar expand={NavigationBar.lg} contextual={Contextual.light} style={{backgroundColor: '#e3f2fd'}}>
                            <Brand type="link">Navbar</Brand>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                            <Collapse id="navbarSupportedContent">
                                <Navigation className="me-auto mb-2 mb-lg-0">
                                    <Hyperlink active>Home</Hyperlink>
                                    <Hyperlink>Link</Hyperlink>
                                    <Dropdown name="Dropdown button" id="navbarDropdown" expanded={false}>
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
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: TEXT */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar expand={NavigationBar.lg} contextual={Contextual.light}>
                            <Brand type="link">Navbar w/ text</Brand>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent3">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                            <Collapse id="navbarSupportedContent3">
                                <Navigation className="me-auto mb-2 mb-lg-0">
                                    <Hyperlink active>Home</Hyperlink>
                                    <Hyperlink>Features</Hyperlink>
                                    <Hyperlink>Pricing</Hyperlink>
                                </Navigation>
                                <Text>Navbar text with an inline element</Text>
                            </Collapse>
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: TEXT */}
                    <NavigationBar contextual={Contextual.light}>
                        <Text>Navbar text with an inline element</Text>
                    </NavigationBar>
                    {/** NAVIGATION BAR: FORM BUTTON */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar contextual={Contextual.light}>
                            <Form className="justify-content-start">
                                <Button className="me-2" contextual={Contextual.success} outline>Main Button</Button>
                                <Button outline size={Button.sm} contextual={Contextual.success} >Smaller  Button</Button>
                            </Form>
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: FORM EMAIL */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar contextual={Contextual.light}>
                            <InputGroup>
                                <InputText id="btn-group-addon-3" placeholder="Input group example" label="Input group example" description="@" />
                            </InputGroup>
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: FORM + BRAND */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar contextual={Contextual.light}>
                            <Brand type="link">Navbar</Brand>
                            <Form className="d-flex">
                                <Input type="search" placeholder="Search" label="Search" className="me-2" />
                                <Button type="submit" outline contextual={Contextual.success}>Search</Button>
                            </Form>
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: FORM */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar contextual={Contextual.light}>
                            <Form className="d-flex">
                                <Input type="search" placeholder="Search" label="Search" className="me-2" />
                                <Button type="submit" outline contextual={Contextual.success}>Search</Button>
                            </Form>
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: NAV */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar expand={NavigationBar.lg} contextual={Contextual.light}>
                            <Brand type="link">Navbar</Brand>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent2">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                            <Collapse id="navbarSupportedContent2">
                                <Navigation>
                                    <Hyperlink active>Home</Hyperlink>
                                    <Hyperlink>Features</Hyperlink>
                                    <Hyperlink>Pricing</Hyperlink>
                                    <Dropdown name="Dropdown button" id="navbarDropdown5" expanded={false}>
                                        <Hyperlink>Action</Hyperlink>
                                        <Hyperlink>Another action</Hyperlink>
                                        <Hyperlink>Something else here</Hyperlink>
                                        <Divider />
                                        <Hyperlink>Separated link</Hyperlink>
                                    </Dropdown>
                                </Navigation>
                            </Collapse>
                        </NavigationBar>
                    </div>
                    <div style={{padding: '5px'}}>
                        <NavigationBar expand={NavigationBar.lg} contextual={Contextual.light}>
                            <Brand type="link">Navbar</Brand>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent2">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                            <Collapse id="navbarSupportedContent2">
                                <Navigation>
                                    <Hyperlink active>Home</Hyperlink>
                                    <Hyperlink>Features</Hyperlink>
                                    <Hyperlink>Pricing</Hyperlink>
                                    <Hyperlink disabled>Disabled</Hyperlink>
                                </Navigation>
                            </Collapse>
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: BRAND + ICON */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar contextual={Contextual.light}>
                            <Brand type="link">
                                <img src={icon} alt="" width="30" height="24" className="d-inline-block align-top" /> Bootstrap
                            </Brand>
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR: BRAND */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar contextual={Contextual.light}>
                            <Brand className="mb-0 h1">Navbar</Brand>
                        </NavigationBar>
                    </div>
                    <div style={{padding: '5px'}}>
                        <NavigationBar contextual={Contextual.light}>
                            <Brand type="link">Navbar</Brand>
                        </NavigationBar>
                    </div>
                    {/** NAVIGATION BAR */}
                    <div style={{padding: '5px'}}>
                        <NavigationBar expand={NavigationBar.lg} contextual={Contextual.light}>
                            <Brand type="link">Navbar</Brand>
                            <Toggle label="Toggle navigation" target="navbarSupportedContent">
                                <span className="navbar-toggler-icon"></span>
                            </Toggle>
                            <Collapse id="navbarSupportedContent">
                                <Navigation className="me-auto mb-2 mb-lg-0">
                                    <Hyperlink active>Home</Hyperlink>
                                    <Hyperlink>Link</Hyperlink>
                                    <Dropdown name="Dropdown button" id="navbarDropdown" expanded={false}>
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
                        </NavigationBar>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}