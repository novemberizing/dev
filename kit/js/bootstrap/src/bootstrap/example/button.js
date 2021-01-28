/**
 * 
 */
import React, { Component } from 'react';

import Button from '../components/button';
import ButtonGroup from '../components/button/group';
import ButtonBar from '../components/button/bar';
import RadioBtn from '../components/button/radio';
import CheckboxBtn from '../components/button/checkbox';
import Input from '../components/input';
import InputGroup from '../components/input/group';
import InputText from '../components/input/text';
import Hyperlink from '../components/hyperlink';
import Context from '../context';

import Contextual from '../contextual';

export default class ExampleButtonView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** CLOSE BUTTON */}
                    <div style={{padding: '5px', backgroundColor: '#000000'}}>
                        <Button type="close" white></Button>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Button type="close" disabled></Button>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Button type="close"></Button>
                    </div>
                    {/** BUTTON BAR SIZE */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="First group" className="me-2" size={ButtonGroup.lg}>
                            <Button contextual={Contextual.dark} outline>Left</Button>
                            <Button contextual={Contextual.dark} outline>Middle</Button>
                            <Button contextual={Contextual.dark} outline>Right</Button>
                        </ButtonGroup>
                    </div>
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="First group" className="me-2">
                            <Button contextual={Contextual.dark} outline>Left</Button>
                            <Button contextual={Contextual.dark} outline>Middle</Button>
                            <Button contextual={Contextual.dark} outline>Right</Button>
                        </ButtonGroup>
                    </div>
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="First group" className="me-2" size={ButtonGroup.sm}>
                            <Button contextual={Contextual.dark} outline>Left</Button>
                            <Button contextual={Contextual.dark} outline>Middle</Button>
                            <Button contextual={Contextual.dark} outline>Right</Button>
                        </ButtonGroup>
                    </div>
                    {/** BUTTON TOOLBAR */}
                    <div style={{padding: '5px'}}>
                        <ButtonBar label="Toolbar with button groups" className="justify-content-between">
                            <ButtonGroup label="First group" className="me-2">
                                <Button contextual={Contextual.secondary}>1</Button>
                                <Button contextual={Contextual.secondary}>2</Button>
                                <Button contextual={Contextual.secondary}>3</Button>
                                <Button contextual={Contextual.secondary}>4</Button>
                            </ButtonGroup>
                            <InputGroup>
                                <InputText id="btn-group-addon-1" placeholder="Input group example" label="Input group example" description="@" />
                            </InputGroup>
                        </ButtonBar>
                    </div>
                    <div style={{padding: '5px'}}>
                        <ButtonBar label="Toolbar with button groups" className="mb-3">
                            <ButtonGroup label="First group" className="me-2">
                                <Button contextual={Contextual.secondary}>1</Button>
                                <Button contextual={Contextual.secondary}>2</Button>
                                <Button contextual={Contextual.secondary}>3</Button>
                                <Button contextual={Contextual.secondary}>4</Button>
                            </ButtonGroup>
                            <InputGroup>
                                <InputText id="btn-group-addon-2" placeholder="Input group example" label="Input group example" description="@" />
                            </InputGroup>
                        </ButtonBar>
                    </div>
                    {/** BUTTON TOOLBAR */}
                    <div style={{padding: '5px'}}>
                        <ButtonBar label="Toolbar with button group">
                            <ButtonGroup label="First group" className="me-2">
                                <Button contextual={Contextual.primary}>1</Button>
                                <Button contextual={Contextual.primary}>2</Button>
                                <Button contextual={Contextual.primary}>3</Button>
                                <Button contextual={Contextual.primary}>4</Button>
                            </ButtonGroup>
                            <ButtonGroup label="Second group" className="me-2">
                                <Button contextual={Contextual.secondary}>5</Button>
                                <Button contextual={Contextual.secondary}>6</Button>
                                <Button contextual={Contextual.secondary}>7</Button>
                            </ButtonGroup>
                            <ButtonGroup label="Third group">
                                <Button contextual={Contextual.info}>8</Button>
                            </ButtonGroup>
                        </ButtonBar>
                    </div>
                    {/** BUTTON GROUP: CHECKBOX */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Basic mixed styles example">
                            <RadioBtn contextual={Contextual.primary} id="btnradio1" name="btnradio" value="1" outline defaultChecked>Left</RadioBtn>
                            <RadioBtn contextual={Contextual.primary} id="btnradio2" name="btnradio" value="2" outline>Middle</RadioBtn>
                            <RadioBtn contextual={Contextual.primary} id="btnradio3" name="btnradio" value="3" outline>Right</RadioBtn>
                        </ButtonGroup>
                    </div>
                    {/** BUTTON GROUP: CHECKBOX */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Basic mixed styles example">
                            <CheckboxBtn contextual={Contextual.primary} id="btncheck1" value="1" outline>Left</CheckboxBtn>
                            <CheckboxBtn contextual={Contextual.primary} id="btncheck2" value="2" outline>Middle</CheckboxBtn>
                            <CheckboxBtn contextual={Contextual.primary} id="btncheck3" value="3" outline>Right</CheckboxBtn>
                        </ButtonGroup>
                    </div>
                    {/** BUTTON GROUP: OUTLINED */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Basic mixed styles example">
                            <Button contextual={Contextual.primary} outline>Left</Button>
                            <Button contextual={Contextual.primary} outline>Middle</Button>
                            <Button contextual={Contextual.primary} outline>Right</Button>
                        </ButtonGroup>
                    </div>
                    {/** BUTTON GROUP: MIXED STYLE */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Basic mixed styles example">
                            <Button contextual={Contextual.danger}>Left</Button>
                            <Button contextual={Contextual.warning}>Middle</Button>
                            <Button contextual={Contextual.success}>Right</Button>
                        </ButtonGroup>
                    </div>
                    {/** BUTTON GROUP: ACTIVE */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Basic example">
                            <Button contextual={Contextual.primary} active>Left</Button>
                            <Button contextual={Contextual.primary}>Middle</Button>
                            <Button contextual={Contextual.primary}>Right</Button>
                        </ButtonGroup>
                    </div>
                    {/** BUTTON GROUP */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Basic example">
                            <Button contextual={Contextual.primary}>Left</Button>
                            <Button contextual={Contextual.primary}>Middle</Button>
                            <Button contextual={Contextual.primary}>Right</Button>
                        </ButtonGroup>
                    </div>
                    
                    
                    
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} toggle>Button</Button>
                        <Button contextual={Contextual.primary} toggle active>Button</Button>
                        <Button contextual={Contextual.primary} toggle disabled>Button</Button>
                    </div>
                    {/** BUTTON: BLOCK */}
                    <div style={{padding: '5px'}}>
                        <div className="d-grid gap-2 d-md-flex justify-content-md-end">
                            <Button contextual={Contextual.primary} className="me-md-2">Button</Button>
                            <Button contextual={Contextual.primary}>Button</Button>
                        </div>
                    </div>
                    <div style={{padding: '5px'}}>
                        <div className="d-grid gap-2 col-6 mx-auto">
                            <Button contextual={Contextual.primary}>Button</Button>
                            <Button contextual={Contextual.primary}>Button</Button>
                        </div>
                    </div>
                    <div style={{padding: '5px'}}>
                        <div className="d-grid gap-2 d-md-block">
                            <Button contextual={Contextual.primary}>Button</Button>
                            <Button contextual={Contextual.primary}>Button</Button>
                        </div>
                    </div>
                    <div style={{padding: '5px'}}>
                        <div className="d-grid gap-2">
                            <Button contextual={Contextual.primary}>Button</Button>
                            <Button contextual={Contextual.primary}>Button</Button>
                        </div>
                    </div>
                    {/** BUTTON: DISABLED - HYPERLINK BUTTON */}
                    <div style={{padding: '5px'}}>
                        <Hyperlink role="button" contextual={Contextual.primary} size={Button.lg} disabled>Primary link</Hyperlink>
                        <Hyperlink role="button" contextual={Contextual.secondary} size={Button.lg} disabled>link</Hyperlink>
                    </div>
                    {/** BUTTON: DISABLED */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} size={Button.lg} disabled>Primary button</Button>
                        <Button contextual={Contextual.secondary} size={Button.lg} disabled>button</Button>                    
                    </div>
                    {/** BUTTON: SIZE */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} size={Button.lg}>Large button</Button>
                        <Button contextual={Contextual.secondary} size={Button.lg}>Large button</Button>
                        <Button contextual={Contextual.primary} size={Button.sm}>Small button</Button>
                        <Button contextual={Contextual.secondary} size={Button.sm}>Small button</Button>
                    </div>
                    {/** BUTTON: OUTLINE */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary} outline>primary</Button>
                        <Button contextual={Contextual.secondary} outline>secondary</Button>
                        <Button contextual={Contextual.danger} outline>danger</Button>
                        <Button contextual={Contextual.warning} outline>warning</Button>
                        <Button contextual={Contextual.info} outline>info</Button>
                        <Button contextual={Contextual.success} outline>success</Button>
                        <Button contextual={Contextual.light} outline>light</Button>
                        <Button contextual={Contextual.dark} outline>dark</Button>
                    </div>
                    {/** BUTTON: HYPERLINK, INPUT */}
                    <div style={{padding: '5px'}}>
                        <Hyperlink role="button" contextual={Contextual.primary}>Link</Hyperlink>
                        <Button type="submit" contextual={Contextual.primary}>Button</Button>
                        <Input type="button" contextual={Contextual.primary}>Input</Input>
                        <Input type="submit" contextual={Contextual.primary}>Submit</Input>
                        <Input type="reset" contextual={Contextual.primary}>Reset</Input>
                    </div>
                    {/** BUTTON */}
                    <div style={{padding: '5px'}}>
                        <Button contextual={Contextual.primary}>primary</Button>
                        <Button contextual={Contextual.secondary}>secondary</Button>
                        <Button contextual={Contextual.danger}>danger</Button>
                        <Button contextual={Contextual.warning}>warning</Button>
                        <Button contextual={Contextual.info}>info</Button>
                        <Button contextual={Contextual.success}>success</Button>
                        <Button contextual={Contextual.light}>light</Button>
                        <Button contextual={Contextual.dark}>dark</Button>
                        <Button type="link">link</Button>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}