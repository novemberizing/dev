/**
 * 
 */
import React, { Component } from 'react';

import CardGroup from '../components/card/group';
import Card from '../components/card';
import Title from '../components/title';
import Header from '../components/header';
import Body from '../components/body';
import Footer from '../components/footer';
import Hyperlink from '../components/hyperlink';
import Paragraph from '../components/paragraph';
import Tab from '../components/tab';
import Blockquote from '../components/blockquote';
import List from '../components/list';
import ListItem from '../components/list/item';
import Subtitle from '../components/subtitle';
import Context from '../context';

import Contextual from '../contextual';

import sample from '../../sample.jpg';

export default class ExampleCardView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** CARD: GRID */}
                    <div style={{padding: '5px'}}>
                        <div className="row row-cols-1 row-cols-md-3 g-4">
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}} className="h-100">
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}} className="h-100">
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}} className="h-100">
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}} className="h-100">
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                        </div>
                    </div>
                    {/** CARD: GRID */}
                    <div style={{padding: '5px'}}>
                        <div className="row row-cols-1 row-cols-md-3 g-4">
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}}>
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}}>
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}}>
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}}>
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                        </div>
                    </div>
                    {/** CARD: GRID */}
                    <div style={{padding: '5px'}}>
                        <div className="row row-cols-1 row-cols-md-2 g-4">
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}}>
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}}>
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}}>
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col">
                                <Card image={{src: sample, alt: 'alt'}}>
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>
                                            This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                        </Paragraph>
                                    </Body>
                                </Card>
                            </div>
                        </div>
                    </div>
                    {/** CARD: GROUP */}
                    <div style={{padding: '5px'}}>
                        <CardGroup>
                            <Card image={{src: sample, alt: 'alt'}}>
                                <Body>
                                    <Title size={5}>Card title</Title>
                                    <Paragraph>
                                        This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                    </Paragraph>
                                </Body>
                                <Footer>
                                    <small className="text-muted">Last updated 3 mins ago</small>
                                </Footer>
                            </Card>
                            <Card image={{src: sample, alt: 'alt'}}>
                                <Body>
                                    <Title size={5}>Card title</Title>
                                    <Paragraph>
                                        This card has supporting text below as a natural lead-in to additional content.
                                    </Paragraph>
                                </Body>
                                <Footer>
                                    <small className="text-muted">Last updated 3 mins ago</small>
                                </Footer>
                            </Card>
                            <Card image={{src: sample, alt: 'alt'}}>
                                <Body>
                                    <Title size={5}>Card title</Title>
                                    <Paragraph>
                                    This is a wider card with supporting text below as a natural lead-in to additional content. This card has even longer content than the first to show that equal height action.
                                    </Paragraph>
                                </Body>
                                <Footer>
                                    <small className="text-muted">Last updated 3 mins ago</small>
                                </Footer>
                            </Card>
                        </CardGroup>
                    </div>
                    {/** CARD: GROUP */}
                    <div style={{padding: '5px'}}>
                        <CardGroup>
                            <Card image={{src: sample, alt: 'alt'}}>
                                <Body>
                                    <Title size={5}>Card title</Title>
                                    <Paragraph>
                                        This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                    </Paragraph>
                                    <Paragraph>
                                        <small className="text-muted">Last updated 3 mins ago</small>
                                    </Paragraph>
                                </Body>
                            </Card>
                            <Card image={{src: sample, alt: 'alt'}}>
                                <Body>
                                    <Title size={5}>Card title</Title>
                                    <Paragraph>
                                        This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                    </Paragraph>
                                    <Paragraph>
                                        <small className="text-muted">Last updated 3 mins ago</small>
                                    </Paragraph>
                                </Body>
                            </Card>
                            <Card image={{src: sample, alt: 'alt'}}>
                                <Body>
                                    <Title size={5}>Card title</Title>
                                    <Paragraph>
                                        This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.
                                    </Paragraph>
                                    <Paragraph>
                                        <small className="text-muted">Last updated 3 mins ago</small>
                                    </Paragraph>
                                </Body>
                            </Card>
                        </CardGroup>
                    </div>
                    {/** CARD: MIXIN */}
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.success} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header className="bg-transparent" border={Contextual.success}>Header</Header>
                            <Body className="text-success">
                                <Title size={5}>Success card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                            <Footer className="bg-transparent" border={Contextual.success}>Footer</Footer>
                        </Card>                    
                    </div>
                    {/** CARD STYLE */}
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.secondary} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.primary} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.danger} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.warning} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.info} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.success} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.dark} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card border={Contextual.light} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD STYLE */}
                    <div style={{padding: '5px'}}>
                        <Card contextual={Contextual.light} style={{maxWidth: '18rem'}} className="mb-3 text-dark">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Light card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card contextual={Contextual.dark} style={{maxWidth: '18rem'}} className="mb-3 text-white">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Dark card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card contextual={Contextual.info} style={{maxWidth: '18rem'}} className="mb-3 text-white">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Info card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card contextual={Contextual.warning} style={{maxWidth: '18rem'}} className="mb-3 text-white">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Warning card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card contextual={Contextual.danger} style={{maxWidth: '18rem'}} className="mb-3 text-white">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Danger card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card contextual={Contextual.success} style={{maxWidth: '18rem'}} className="mb-3 text-white">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Success card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card contextual={Contextual.secondary} style={{maxWidth: '18rem'}} className="mb-3 text-white">
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Secondary card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card style={{maxWidth: '18rem'}} className="mb-3 text-white" contextual={Contextual.primary}>
                            <Header>Header</Header>
                            <Body>
                                <Title size={5}>Primary card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD HORIZONTAL */}
                    <div style={{padding: '5px'}}>
                        <Card className="mb-3" style={{maxWidth: '540px'}}>
                            <div className="row g-0">
                                <div className="col-md-4">
                                    <img src={sample} width="180" height="400" alt="alt" />
                                </div>
                                <div className="col-md-8">
                                    <Body>
                                        <Title size={5}>Card title</Title>
                                        <Paragraph>This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.</Paragraph>
                                        <Paragraph><small className="text-muted">Last updated 3 mins ago</small></Paragraph>
                                    </Body>
                                </div>
                            </div>
                        </Card>
                    </div>
                    {/** CARD IMAGE BOTTO */}
                    <div style={{padding: '5px'}}>
                        <Card image={{src: sample, alt: "alert", bottom: true}} style={{width: "18rem"}}>
                            <Body overlay>
                                <Title size={5}>Card title</Title>
                                <Paragraph>This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.</Paragraph>
                                <Paragraph><small className="text-muted">Last updated 3 mins ago</small></Paragraph>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD NAVIGATION */}
                    <div style={{padding: '5px'}}>
                        <Card className="text-center" style={{width: "18rem"}}>
                            <Header>
                                <Tab pill>
                                    <Hyperlink active>Active</Hyperlink>
                                    <Hyperlink>Link</Hyperlink>
                                    <Hyperlink disabled>Disable</Hyperlink>
                                </Tab>
                            </Header>
                            <Body>
                                <Title size={5}>Special title treatment</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD NAVIGATION */}
                    <div style={{padding: '5px'}}>
                        <Card className="text-center" style={{width: "18rem"}}>
                            <Header>
                                <Tab>
                                    <Hyperlink active>Active</Hyperlink>
                                    <Hyperlink>Link</Hyperlink>
                                    <Hyperlink disabled>Disable</Hyperlink>
                                </Tab>
                            </Header>
                            <Body>
                                <Title size={5}>Special title treatment</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD TEXT ALIGN */}
                    <div style={{padding: '5px'}}>
                        <Card className="text-center" style={{width: "18rem"}}>
                            <Header>Featured</Header>
                            <Body>
                                <Title size={5}>Special title treatment</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card className="text-end" style={{width: "18rem"}}>
                            <Header>Featured</Header>
                            <Body>
                                <Title size={5}>Special title treatment</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD SIZE */}
                    <div style={{padding: '5px'}}>
                        <Card className="w-75">
                            <Body>
                                <Title size={5}>Card title</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Button</Hyperlink>
                            </Body>
                        </Card>
                        <Card className="w-50">
                            <Body>
                                <Title size={5}>Card title</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Button</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <div className="row">
                            <div className="col-sm-6">
                                <Card>
                                    <Header>Featured</Header>
                                    <Body>
                                        <Title size={5}>Special title treatment</Title>
                                        <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                        <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                                    </Body>
                                </Card>
                            </div>
                            <div className="col-sm-6">
                                <Card>
                                    <Header>Featured</Header>
                                    <Body>
                                        <Title size={5}>Special title treatment</Title>
                                        <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                        <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                                    </Body>
                                </Card>
                            </div>
                        </div>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card className="text-center">
                            <Header>Featured</Header>
                            <Body>
                                <Title size={5}>Special title treatment</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                            <Footer className="text-muted">
                                2 days ago
                            </Footer>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card className="text-center">
                            <Header>Featured</Header>
                            <Body>
                                <Title size={5}>Special title treatment</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD: HEADER & FOOTER */}
                    <div style={{padding: '5px'}}>
                        <Card>
                            <Header size={5}>Quote</Header>
                            <Body>
                                <Blockquote className="mb-0">
                                    <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer posuere erat a ante.</Paragraph>
                                    <Footer>Someone famous in <cite title="Source Title">Source Title</cite></Footer>
                                </Blockquote>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card>
                            <Header size={5}>Featured</Header>
                            <Body>
                                <Title size={5}>Special title treatment</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card>
                            <Header>Featured</Header>
                            <Body>
                                <Title size={5}>Special title treatment</Title>
                                <Paragraph>With supporting text below as a natural lead-in to additional content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD: KITCHEN */}
                    <div style={{padding: '5px'}}>
                        <Card image={{src: sample, alt: "alert"}} style={{width: "18rem"}}>
                            <Body>
                                <Title size={5}>Card title</Title>
                                <Paragraph>
                                    Some quick example text to build on the card title and make up the bulk of the card's content.
                                </Paragraph>
                            </Body>
                            <List flush>
                                <ListItem>Cras justo odio</ListItem>
                                <ListItem>Dapibus ac facilisis in</ListItem>
                                <ListItem>Vestibulum at eros</ListItem>
                            </List>
                            <Body>
                                <Hyperlink>Card Link</Hyperlink>
                                <Hyperlink>Another Link</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD: LIST GROUP */}
                    <div style={{padding: '5px'}}>
                        <Card style={{width: "18rem"}}>
                            <List flush>
                                <ListItem>Cras justo odio</ListItem>
                                <ListItem>Dapibus ac facilisis in</ListItem>
                                <ListItem>Vestibulum at eros</ListItem>
                            </List>
                            <Footer>Featured</Footer>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card style={{width: "18rem"}}>
                            <Header>Featured</Header>
                            <List flush>
                                <ListItem>Cras justo odio</ListItem>
                                <ListItem>Dapibus ac facilisis in</ListItem>
                                <ListItem>Vestibulum at eros</ListItem>
                            </List>
                        </Card>
                    </div>
                    {/** CARD */}
                    <div style={{padding: '5px'}}>
                        <Card image={{src: sample, alt: "alert"}} style={{width: "18rem"}}>
                            <Body>
                                <Paragraph>
                                    Some quick example text to build on the card title and make up the bulk of the card's content.
                                </Paragraph>
                            </Body>
                        </Card>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Card style={{width: '18rem'}}>
                            <Body>
                                <Title size={5}>Card title</Title>
                                <Subtitle size={6} className="mb-2 text-muted">Card subtitle</Subtitle>
                                <Paragraph>
                                    Some quick example text to build on the card title and make up the bulk of the card's content.
                                </Paragraph>
                                <Hyperlink>Card link</Hyperlink>
                                <Hyperlink>Another link</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                    {/** CARD */}
                    <div style={{padding: '5px'}}>
                        <Card>
                            <Body>
                                This is some text within a card body.
                            </Body>
                        </Card>
                    </div>
                    {/** CARD */}
                    <div style={{padding: '5px'}}>
                        <Card image={{src: sample, alt: "alert"}} style={{width: "18rem"}}>
                            <Body>
                                <Title size={5}>Card title</Title>
                                <Paragraph>Some quick example text to build on the card title and make up the bulk of the card's content.</Paragraph>
                                <Hyperlink role="button" contextual={Contextual.primary}>Go somewhere</Hyperlink>
                            </Body>
                        </Card>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}