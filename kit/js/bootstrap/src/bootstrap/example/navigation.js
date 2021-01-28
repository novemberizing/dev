/**
 * 
 */
import React, { Component } from 'react';

import Tab from '../components/tab';
import Navigation from '../components/navigation';
import Hyperlink from '../components/hyperlink';
import Panel from '../components/panel';
import Dropdown from '../components/dropdown';
import Divider from '../components/divider';
import Context from '../context';

export default class ExampleNavigationView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** EVENT */}
                    <div style={{padding: '5px'}}>
                        <Tab id="myTab" role="tablist" onShow={event=>console.log("show", event)}
                                                    onShown={event=>console.log("shown", event)}
                                                    onHide={event=>console.log("hide", event)}
                                                    onHidden={event=>console.log("hidden", event)}>
                            <Panel id="home1" name="Home" active>Raw denim you probably haven't heard of them jean shorts Austin. Nesciunt tofu stumptown aliqua, retro synth master cleanse. Mustache cliche tempor, williamsburg carles vegan helvetica. Reprehenderit butcher retro keffiyeh dreamcatcher synth. Cosby sweater eu banh mi, qui irure terry richardson ex squid. Aliquip placeat salvia cillum iphone. Seitan aliquip quis cardigan american apparel, butcher voluptate nisi qui.</Panel>
                            <Panel id="profile1" name="Profile">Food truck fixie locavore, accusamus mcsweeney's marfa nulla single-origin coffee squid. Exercitation +1 labore velit, blog sartorial PBR leggings next level wes anderson artisan four loko farm-to-table craft beer twee. Qui photo booth letterpress, commodo enim craft beer mlkshk aliquip jean shorts ullamco ad vinyl cillum PBR. Homo nostrud organic, assumenda labore aesthetic magna delectus mollit. Keytar helvetica VHS salvia yr, vero magna velit sapiente labore stumptown. Vegan fanny pack odio cillum wes anderson 8-bit, sustainable jean shorts beard ut DIY ethical culpa terry richardson biodiesel. Art party scenester stumptown, tumblr butcher vero sint qui sapiente accusamus tattooed echo park.</Panel>
                            <Panel id="contact1" name="Contact">Etsy mixtape wayfarers, ethical wes anderson tofu before they sold out mcsweeney's organic lomo retro fanny pack lo-fi farm-to-table readymade. Messenger bag gentrify pitchfork tattooed craft beer, iphone skateboard locavore carles etsy salvia banksy hoodie helvetica. DIY synth PBR banksy irony. Leggings gentrify squid 8-bit cred pitchfork. Williamsburg banh mi whatever gluten-free, carles pitchfork biodiesel fixie etsy retro mlkshk vice blog. Scenester cred you probably haven't heard of them, vinyl craft beer blog stumptown. Pitchfork sustainable tofu synth chambray yr.</Panel>
                        </Tab>
                    </div>
                    {/** PILL VERTICAL */}
                    <div style={{padding: '5px'}} className="d-flex align-items-start">
                        <Tab id="myTab3" role="tablist" pill className="flex-column me-3" vertical>
                            <Panel id="home2" name="Home" active>Raw denim you probably haven't heard of them jean shorts Austin. Nesciunt tofu stumptown aliqua, retro synth master cleanse. Mustache cliche tempor, williamsburg carles vegan helvetica. Reprehenderit butcher retro keffiyeh dreamcatcher synth. Cosby sweater eu banh mi, qui irure terry richardson ex squid. Aliquip placeat salvia cillum iphone. Seitan aliquip quis cardigan american apparel, butcher voluptate nisi qui.</Panel>
                            <Panel id="profile2" name="Profile">Food truck fixie locavore, accusamus mcsweeney's marfa nulla single-origin coffee squid. Exercitation +1 labore velit, blog sartorial PBR leggings next level wes anderson artisan four loko farm-to-table craft beer twee. Qui photo booth letterpress, commodo enim craft beer mlkshk aliquip jean shorts ullamco ad vinyl cillum PBR. Homo nostrud organic, assumenda labore aesthetic magna delectus mollit. Keytar helvetica VHS salvia yr, vero magna velit sapiente labore stumptown. Vegan fanny pack odio cillum wes anderson 8-bit, sustainable jean shorts beard ut DIY ethical culpa terry richardson biodiesel. Art party scenester stumptown, tumblr butcher vero sint qui sapiente accusamus tattooed echo park.</Panel>
                            <Panel id="contact2" name="Contact">Etsy mixtape wayfarers, ethical wes anderson tofu before they sold out mcsweeney's organic lomo retro fanny pack lo-fi farm-to-table readymade. Messenger bag gentrify pitchfork tattooed craft beer, iphone skateboard locavore carles etsy salvia banksy hoodie helvetica. DIY synth PBR banksy irony. Leggings gentrify squid 8-bit cred pitchfork. Williamsburg banh mi whatever gluten-free, carles pitchfork biodiesel fixie etsy retro mlkshk vice blog. Scenester cred you probably haven't heard of them, vinyl craft beer blog stumptown. Pitchfork sustainable tofu synth chambray yr.</Panel>
                        </Tab>
                    </div>
                    {/** TAB: CONTENT */}
                    <div style={{padding: '5px'}}>
                        <Tab id="myTab" role="tablist" pill>
                            <Panel id="home1" name="Home" active>Raw denim you probably haven't heard of them jean shorts Austin. Nesciunt tofu stumptown aliqua, retro synth master cleanse. Mustache cliche tempor, williamsburg carles vegan helvetica. Reprehenderit butcher retro keffiyeh dreamcatcher synth. Cosby sweater eu banh mi, qui irure terry richardson ex squid. Aliquip placeat salvia cillum iphone. Seitan aliquip quis cardigan american apparel, butcher voluptate nisi qui.</Panel>
                            <Panel id="profile1" name="Profile">Food truck fixie locavore, accusamus mcsweeney's marfa nulla single-origin coffee squid. Exercitation +1 labore velit, blog sartorial PBR leggings next level wes anderson artisan four loko farm-to-table craft beer twee. Qui photo booth letterpress, commodo enim craft beer mlkshk aliquip jean shorts ullamco ad vinyl cillum PBR. Homo nostrud organic, assumenda labore aesthetic magna delectus mollit. Keytar helvetica VHS salvia yr, vero magna velit sapiente labore stumptown. Vegan fanny pack odio cillum wes anderson 8-bit, sustainable jean shorts beard ut DIY ethical culpa terry richardson biodiesel. Art party scenester stumptown, tumblr butcher vero sint qui sapiente accusamus tattooed echo park.</Panel>
                            <Panel id="contact1" name="Contact">Etsy mixtape wayfarers, ethical wes anderson tofu before they sold out mcsweeney's organic lomo retro fanny pack lo-fi farm-to-table readymade. Messenger bag gentrify pitchfork tattooed craft beer, iphone skateboard locavore carles etsy salvia banksy hoodie helvetica. DIY synth PBR banksy irony. Leggings gentrify squid 8-bit cred pitchfork. Williamsburg banh mi whatever gluten-free, carles pitchfork biodiesel fixie etsy retro mlkshk vice blog. Scenester cred you probably haven't heard of them, vinyl craft beer blog stumptown. Pitchfork sustainable tofu synth chambray yr.</Panel>
                        </Tab>
                    </div>
                    {/** TAB: CONTENT */}
                    <div style={{padding: '5px'}}>
                        <Tab id="myTab2" role="tablist">
                            <Panel id="home" name="Home" active>Raw denim you probably haven't heard of them jean shorts Austin. Nesciunt tofu stumptown aliqua, retro synth master cleanse. Mustache cliche tempor, williamsburg carles vegan helvetica. Reprehenderit butcher retro keffiyeh dreamcatcher synth. Cosby sweater eu banh mi, qui irure terry richardson ex squid. Aliquip placeat salvia cillum iphone. Seitan aliquip quis cardigan american apparel, butcher voluptate nisi qui.</Panel>
                            <Panel id="profile" name="Profile">Food truck fixie locavore, accusamus mcsweeney's marfa nulla single-origin coffee squid. Exercitation +1 labore velit, blog sartorial PBR leggings next level wes anderson artisan four loko farm-to-table craft beer twee. Qui photo booth letterpress, commodo enim craft beer mlkshk aliquip jean shorts ullamco ad vinyl cillum PBR. Homo nostrud organic, assumenda labore aesthetic magna delectus mollit. Keytar helvetica VHS salvia yr, vero magna velit sapiente labore stumptown. Vegan fanny pack odio cillum wes anderson 8-bit, sustainable jean shorts beard ut DIY ethical culpa terry richardson biodiesel. Art party scenester stumptown, tumblr butcher vero sint qui sapiente accusamus tattooed echo park.</Panel>
                            <Panel id="contact" name="Contact">Etsy mixtape wayfarers, ethical wes anderson tofu before they sold out mcsweeney's organic lomo retro fanny pack lo-fi farm-to-table readymade. Messenger bag gentrify pitchfork tattooed craft beer, iphone skateboard locavore carles etsy salvia banksy hoodie helvetica. DIY synth PBR banksy irony. Leggings gentrify squid 8-bit cred pitchfork. Williamsburg banh mi whatever gluten-free, carles pitchfork biodiesel fixie etsy retro mlkshk vice blog. Scenester cred you probably haven't heard of them, vinyl craft beer blog stumptown. Pitchfork sustainable tofu synth chambray yr.</Panel>
                        </Tab>
                    </div>
                    {/** PILL: DROPDOWN */}
                    <div style={{padding: '5px'}}>
                        <Navigation pill>
                            <Hyperlink active>Active</Hyperlink>
                            <Dropdown type="link" name="Dropdown button" id="dropdownMenuButton2" expanded={false}>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Disabled</Hyperlink>
                        </Navigation>                    
                    </div>
                    {/** TAB: DROPDOWN */}
                    <div style={{padding: '5px'}}>
                        <Tab>
                            <Hyperlink active>Active</Hyperlink>
                            <Dropdown type="link" name="Dropdown button" id="dropdownMenuButton" expanded={false}>
                                <Hyperlink>Action</Hyperlink>
                                <Hyperlink>Another action</Hyperlink>
                                <Hyperlink>Something else here</Hyperlink>
                                <Divider />
                                <Hyperlink>Separated link</Hyperlink>
                            </Dropdown>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Disabled</Hyperlink>
                        </Tab>
                    </div>
                    {/** NAVIGATION: FLEX COLUMN FLEX SM ROW */}
                    <div style={{padding: '5px'}}>
                        <Navigation pill className="flex-column flex-sm-row">
                            <Hyperlink active className="flex-sm-fill text-sm-center">Active</Hyperlink>
                            <Hyperlink className="flex-sm-fill text-sm-center">Much longer nav link</Hyperlink>
                            <Hyperlink className="flex-sm-fill text-sm-center">Link</Hyperlink>
                            <Hyperlink disabled className="flex-sm-fill text-sm-center">Disabled</Hyperlink>
                        </Navigation>                    
                    </div>
                    {/** NAVIGATION: FILL & JUSTIFY */}
                    <div style={{padding: '5px'}}>
                        <Navigation pill justified>
                            <Hyperlink active>Active</Hyperlink>
                            <Hyperlink>Much longer nav link</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Disabled</Hyperlink>
                        </Navigation>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Navigation pill fill>
                            <Hyperlink active>Active</Hyperlink>
                            <Hyperlink>Much longer nav link</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Disabled</Hyperlink>
                        </Navigation>
                    </div>
                    {/** NAVIGATION: PILL */}
                    <div style={{padding: '5px'}}>
                        <Navigation pill>
                            <Hyperlink active>Active</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Link</Hyperlink>
                        </Navigation>
                    </div>
                    {/** TAB */}
                    <div style={{padding: '5px'}}>
                        <Tab>
                            <Hyperlink active>Active</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Link</Hyperlink>
                        </Tab>
                    </div>
                    {/** NAVIGATION: STYLE: VERTICAL ALIGNMENT */}
                    <div style={{padding: '5px'}}>
                        <Navigation className="flex-column">
                            <Hyperlink active>Active</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Link</Hyperlink>
                        </Navigation>
                    </div>
                    {/** NAVIGATION: STYLE: HORIZONTAL ALIGNMENT */}
                    <div style={{padding: '5px'}}>
                        <Navigation className="justify-content-end">
                            <Hyperlink active>Active</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Link</Hyperlink>
                        </Navigation>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Navigation className="justify-content-center">
                            <Hyperlink active>Active</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Link</Hyperlink>
                        </Navigation>
                    </div>
                    {/** NAVIGATION */}
                    <div style={{padding: '5px'}}>
                        <Navigation>
                            <Hyperlink active>Active</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink>Link</Hyperlink>
                            <Hyperlink disabled>Link</Hyperlink>
                        </Navigation>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}