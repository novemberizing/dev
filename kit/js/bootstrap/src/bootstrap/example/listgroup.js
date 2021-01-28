/**
 * 
 */
import React, { Component } from 'react';

import List from '../components/list';
import ListItem from '../components/list/item';
import Hyperlink from '../components/hyperlink';
import Badge from '../components/badge';
import Tab from '../components/tab';
import Panel from '../components/panel';
import Input from '../components/input';
import Button from '../components/button';
import Context from '../context';

import Breakpoint from '../breakpoint';
import Contextual from '../contextual';

export default class ExampleListGroupView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** LISTGROUP: JAVASCRIPT BEHAVIOR */}
                    <div style={{padding: '5px'}} className="d-flex align-items-start">
                        <Tab id="myTab3" role="tablist" className="flex-column me-3" vertical>
                            <Panel id="home2" name="Home" active>Raw denim you probably haven't heard of them jean shorts Austin. Nesciunt tofu stumptown aliqua, retro synth master cleanse. Mustache cliche tempor, williamsburg carles vegan helvetica. Reprehenderit butcher retro keffiyeh dreamcatcher synth. Cosby sweater eu banh mi, qui irure terry richardson ex squid. Aliquip placeat salvia cillum iphone. Seitan aliquip quis cardigan american apparel, butcher voluptate nisi qui.</Panel>
                            <Panel id="profile2" name="Profile">Food truck fixie locavore, accusamus mcsweeney's marfa nulla single-origin coffee squid. Exercitation +1 labore velit, blog sartorial PBR leggings next level wes anderson artisan four loko farm-to-table craft beer twee. Qui photo booth letterpress, commodo enim craft beer mlkshk aliquip jean shorts ullamco ad vinyl cillum PBR. Homo nostrud organic, assumenda labore aesthetic magna delectus mollit. Keytar helvetica VHS salvia yr, vero magna velit sapiente labore stumptown. Vegan fanny pack odio cillum wes anderson 8-bit, sustainable jean shorts beard ut DIY ethical culpa terry richardson biodiesel. Art party scenester stumptown, tumblr butcher vero sint qui sapiente accusamus tattooed echo park.</Panel>
                            <Panel id="contact2" name="Contact">Etsy mixtape wayfarers, ethical wes anderson tofu before they sold out mcsweeney's organic lomo retro fanny pack lo-fi farm-to-table readymade. Messenger bag gentrify pitchfork tattooed craft beer, iphone skateboard locavore carles etsy salvia banksy hoodie helvetica. DIY synth PBR banksy irony. Leggings gentrify squid 8-bit cred pitchfork. Williamsburg banh mi whatever gluten-free, carles pitchfork biodiesel fixie etsy retro mlkshk vice blog. Scenester cred you probably haven't heard of them, vinyl craft beer blog stumptown. Pitchfork sustainable tofu synth chambray yr.</Panel>
                        </Tab>
                    </div>
                    <div style={{padding: '5px'}} className="d-flex align-items-start">
                        <Tab id="myTab3" role="tablist" pill className="flex-column me-3" vertical>
                            <Panel id="home2" name="Home" active>Raw denim you probably haven't heard of them jean shorts Austin. Nesciunt tofu stumptown aliqua, retro synth master cleanse. Mustache cliche tempor, williamsburg carles vegan helvetica. Reprehenderit butcher retro keffiyeh dreamcatcher synth. Cosby sweater eu banh mi, qui irure terry richardson ex squid. Aliquip placeat salvia cillum iphone. Seitan aliquip quis cardigan american apparel, butcher voluptate nisi qui.</Panel>
                            <Panel id="profile2" name="Profile">Food truck fixie locavore, accusamus mcsweeney's marfa nulla single-origin coffee squid. Exercitation +1 labore velit, blog sartorial PBR leggings next level wes anderson artisan four loko farm-to-table craft beer twee. Qui photo booth letterpress, commodo enim craft beer mlkshk aliquip jean shorts ullamco ad vinyl cillum PBR. Homo nostrud organic, assumenda labore aesthetic magna delectus mollit. Keytar helvetica VHS salvia yr, vero magna velit sapiente labore stumptown. Vegan fanny pack odio cillum wes anderson 8-bit, sustainable jean shorts beard ut DIY ethical culpa terry richardson biodiesel. Art party scenester stumptown, tumblr butcher vero sint qui sapiente accusamus tattooed echo park.</Panel>
                            <Panel id="contact2" name="Contact">Etsy mixtape wayfarers, ethical wes anderson tofu before they sold out mcsweeney's organic lomo retro fanny pack lo-fi farm-to-table readymade. Messenger bag gentrify pitchfork tattooed craft beer, iphone skateboard locavore carles etsy salvia banksy hoodie helvetica. DIY synth PBR banksy irony. Leggings gentrify squid 8-bit cred pitchfork. Williamsburg banh mi whatever gluten-free, carles pitchfork biodiesel fixie etsy retro mlkshk vice blog. Scenester cred you probably haven't heard of them, vinyl craft beer blog stumptown. Pitchfork sustainable tofu synth chambray yr.</Panel>
                        </Tab>
                    </div>
                    {/** LISTGROUP: CHECKBOX & RADIO */}
                    <div style={{padding: '5px'}}>
                        <List>
                            <Input type="checkbox" value="1" className="me-1" label="label1">Cras justo odio</Input>
                            <Input type="checkbox" value="2" className="me-1" label="label2">Dapibus ac facilisis in</Input>
                            <Input type="checkbox" value="3" className="me-1" label="label3">Morbi leo risus</Input>
                            <Input type="checkbox" value="4" className="me-1" label="label4">Porta ac consectetur ac</Input>
                            <Input type="checkbox" value="5" className="me-1" label="label5">Vestibulum at eros</Input>
                        </List>
                    </div>
                    {/** LISTGROUP: CONTEXTUAL */}
                    <div style={{padding: '5px'}}>
                        <List>
                            <Hyperlink>Dapibus ac facilisis in</Hyperlink>
                            <Hyperlink contextual={Contextual.primary}>A simple primary list group item</Hyperlink>
                            <Hyperlink contextual={Contextual.secondary}>A simple secondary list group item</Hyperlink>
                            <Hyperlink contextual={Contextual.danger}>A simple danger list group item</Hyperlink>
                            <Hyperlink contextual={Contextual.warning}>A simple warning list group item</Hyperlink>
                            <Hyperlink contextual={Contextual.success}>A simple success list group item</Hyperlink>
                            <Hyperlink contextual={Contextual.info}>A simple info list group item</Hyperlink>
                            <Hyperlink contextual={Contextual.light}>A simple light list group item</Hyperlink>
                            <Hyperlink contextual={Contextual.dark}>A simple dark list group item</Hyperlink>
                        </List>
                    </div>
                    <div style={{padding: '5px'}}>
                        <List>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem contextual={Contextual.primary}>A simple primary list group item</ListItem>
                            <ListItem contextual={Contextual.secondary}>A simple secondary list group item</ListItem>
                            <ListItem contextual={Contextual.danger}>A simple danger list group item</ListItem>
                            <ListItem contextual={Contextual.warning}>A simple warning list group item</ListItem>
                            <ListItem contextual={Contextual.success}>A simple success list group item</ListItem>
                            <ListItem contextual={Contextual.info}>A simple info list group item</ListItem>
                            <ListItem contextual={Contextual.light}>A simple light list group item</ListItem>
                            <ListItem contextual={Contextual.dark}>A simple dark list group item</ListItem>
                        </List>
                    </div>
                    {/** LISTGROUP: HORIZONTAL */}
                    <div style={{padding: '5px'}}>
                        <List horizontal>
                            <ListItem>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                        </List>
                        <List horizontal={Breakpoint.sm}>
                            <ListItem>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                        </List>
                        <List horizontal={Breakpoint.md}>
                            <ListItem>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                        </List>
                        <List horizontal={Breakpoint.lg}>
                            <ListItem>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                        </List>
                        <List horizontal={Breakpoint.xl}>
                            <ListItem>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                        </List>
                        <List horizontal={Breakpoint.xxl}>
                            <ListItem>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                        </List>
                    </div>
                    {/** LISTGROUP: FLUSH */}
                    <div style={{padding: '5px'}}>
                        <List flush>
                            <ListItem>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                            <ListItem>Porta ac consectetur ac</ListItem>
                            <ListItem>Vestibulum at eros</ListItem>
                        </List>
                    </div>
                    {/** LISTGROUP: LINKS AND BUTTONS */}
                    <div style={{padding: '5px'}}>
                        <List>
                            <Button active>Cras justo odio</Button>
                            <Button>Dapibus ac facilisis in</Button>
                            <Button>Morbi leo risus</Button>
                            <Button>Porta ac consectetur ac</Button>
                            <Button disabled>Vestibulum at eros</Button>
                        </List>
                    </div>
                    <div style={{padding: '5px'}}>
                        <List>
                            <Hyperlink active>Cras justo odio</Hyperlink>
                            <Hyperlink>Dapibus ac facilisis in</Hyperlink>
                            <Hyperlink>Morbi leo risus</Hyperlink>
                            <Hyperlink>Porta ac consectetur ac</Hyperlink>
                            <Hyperlink disabled>Vestibulum at eros</Hyperlink>
                        </List>
                    </div>
                    <div style={{padding: '5px'}}>
                        {/** LISTGROUP: DISABLE */}
                        <List>
                            <ListItem disabled>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                            <ListItem>Porta ac consectetur ac</ListItem>
                            <ListItem>Vestibulum at eros</ListItem>
                        </List>
                        {/** LISTGROUP: ACTIVE */}
                        <List>
                            <ListItem active>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                            <ListItem>Porta ac consectetur ac</ListItem>
                            <ListItem>Vestibulum at eros</ListItem>
                        </List>
                        {/** LISTGROUP */}
                        <List>
                            <ListItem>Cras justo odio</ListItem>
                            <ListItem>Dapibus ac facilisis in</ListItem>
                            <ListItem>Morbi leo risus</ListItem>
                            <ListItem>Porta ac consectetur ac</ListItem>
                            <ListItem>Vestibulum at eros</ListItem>
                        </List>
                    </div>
                    {/** LIST GROUP: WITH BADGE */}
                    <div style={{padding: '5px'}}>
                        <List>
                            <Hyperlink active>
                                <div className="d-flex w-100 justify-content-between">
                                    <h5 className="mb-1">List group item heading</h5>
                                    <small>3 days ago</small>
                                </div>
                                <p className="mb-1">Donec id elit non mi porta gravida at eget metus. Maecenas sed diam eget risus varius blandit.</p>
                                <small>Donec id elit non mi porta.</small>
                            </Hyperlink>
                            <Hyperlink>
                                <div className="d-flex w-100 justify-content-between">
                                    <h5 className="mb-1">List group item heading</h5>
                                    <small>3 days ago</small>
                                </div>
                                <p className="mb-1">Donec id elit non mi porta gravida at eget metus. Maecenas sed diam eget risus varius blandit.</p>
                                <small>Donec id elit non mi porta.</small>
                            </Hyperlink>
                            <Hyperlink>
                                <div className="d-flex w-100 justify-content-between">
                                    <h5 className="mb-1">List group item heading</h5>
                                    <small>3 days ago</small>
                                </div>
                                <p className="mb-1">Donec id elit non mi porta gravida at eget metus. Maecenas sed diam eget risus varius blandit.</p>
                                <small>Donec id elit non mi porta.</small>
                            </Hyperlink>
                        </List>
                    </div>
                    {/** LIST GROUP: WITH BADGE */}
                    <div style={{padding: '5px'}}>
                        <List>
                            <ListItem className="d-flex justify-content-between align-items-cente">
                                Cras justo odio
                                <Badge pill contextual={Contextual.primary}>14</Badge>
                            </ListItem>
                            <ListItem className="d-flex justify-content-between align-items-cente">
                                Dapibus ac facilisis in
                                <Badge pill contextual={Contextual.primary}>2</Badge>
                            </ListItem>
                            <ListItem className="d-flex justify-content-between align-items-cente">
                                Morbi leo risus
                                <Badge pill contextual={Contextual.primary}>1</Badge>
                            </ListItem>
                        </List>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}