/**
 * 
 */
import React, { Component } from 'react';

import Blockquote from '../components/blockquote';
import Paragraph from '../components/paragraph';
import Footer from '../components/footer';
import Header from '../components/header';
import Context from '../context';

export default class ExampleView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** EXAMPLE BLOCKQUOTE */}
                    <Blockquote>
                        <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer posuere erat a ante.</Paragraph>
                    </Blockquote>
                    {/** EXAMPLE: BLOCKQUOTE WITH FOOTER */}
                    <Blockquote>
                        <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer posuere erat a ante.</Paragraph>
                        <Footer>
                            Someone famous in <cite title="Source Title">Source Title</cite>
                        </Footer>
                    </Blockquote>
                    {/** EXAMPLE: BLOCKQUOTE */}
                    <Blockquote>
                        <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer posuere erat a ante.</Paragraph>
                    </Blockquote>
                    {/** EXAMPLE: HEADER */}
                    <Header size={1}>h1. Bootstrap heading</Header>
                    <Header size={2}>h1. Bootstrap heading</Header>
                    <Header size={3}>h1. Bootstrap heading</Header>
                    <Header size={4}>h1. Bootstrap heading</Header>
                    <Header size={5}>h1. Bootstrap heading</Header>
                    <Header size={6}>h1. Bootstrap heading</Header>
                </div>
            </Context.Provider>
        );
    }
}