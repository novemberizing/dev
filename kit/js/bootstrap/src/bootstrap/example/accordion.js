/**
 * 
 */
import React, { Component } from 'react';

import Accordion from '../components/accordion';
import AccordionItem from '../components/accordion/item';

import Context from '../context';

export default class ExampleAccordionView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** ACCORDION: FLUSH */}
                    <div style={{padding: '5px'}}>
                        <Accordion id="accordionExample1" flush>
                            <AccordionItem title={{value: "Accordion Item #1", size: 2}}>
                                <strong>This is the first item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
                            </AccordionItem>
                            <AccordionItem title={{value: "Accordion Item #2", size: 2}}>
                                <strong>This is the second item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
                            </AccordionItem>
                            <AccordionItem title={{value: "Accordion Item #3", size: 2}}>
                                <strong>This is the third item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
                            </AccordionItem>
                        </Accordion>
                    </div>
                    {/** ACCORDION */}
                    <div style={{padding: '5px'}}>
                        <Accordion id="accordionExample">
                            <AccordionItem title={{value: "Accordion Item #1", size: 2}} collapse>
                                <strong>This is the first item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
                            </AccordionItem>
                            <AccordionItem title={{value: "Accordion Item #2", size: 2}}>
                                <strong>This is the second item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
                            </AccordionItem>
                            <AccordionItem title={{value: "Accordion Item #3", size: 2}}>
                                <strong>This is the third item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
                            </AccordionItem>
                        </Accordion>
                    </div>
                </div>
            </Context.Provider>
        )
    }
}