/**
 * 
 */
import React, { Component } from 'react';

import Button from '../components/button';
import ButtonGroup from '../components/button/group';
import Dropdown from '../components/dropdown';
import Hyperlink from '../components/hyperlink';
import RadioBtn from '../components/button/radio';
import CheckboxBtn from '../components/button/checkbox';
import Context from '../context';

import Contextual from '../contextual';

export default class ExampleButtonGroupView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** BUTTON GROUP: VERTICAL */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Button group with nested dropdown" vertical>
                            <Button contextual={Contextual.primary}>1</Button>
                            <Button contextual={Contextual.primary}>2</Button>
                            <Dropdown name="Dropdown" id="btnGroupDrop1" contextual={Contextual.primary}>
                                <Hyperlink>Dropdown link</Hyperlink>
                                <Hyperlink>Dropdown link</Hyperlink>
                            </Dropdown>
                            <RadioBtn contextual={Contextual.primary} id="btnradio4" name="btnradio1" value="1" outline>Left</RadioBtn>
                            <RadioBtn contextual={Contextual.primary} id="btnradio5" name="btnradio1" value="2" outline>Middle</RadioBtn>
                            <RadioBtn contextual={Contextual.primary} id="btnradio6" name="btnradio1" value="3" outline>Right</RadioBtn>
                            <CheckboxBtn contextual={Contextual.primary} id="btncheck4" value="1" outline defaultChecked>Left</CheckboxBtn>
                            <CheckboxBtn contextual={Contextual.primary} id="btncheck5" value="2" outline>Middle</CheckboxBtn>
                            <CheckboxBtn contextual={Contextual.primary} id="btncheck6" value="3" outline>Right</CheckboxBtn>
                        </ButtonGroup>
                    </div>
                    {/** BUTTON GROUP: VERTICAL */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Button group with nested dropdown" vertical>
                            <Button contextual={Contextual.primary}>1</Button>
                            <Button contextual={Contextual.primary}>2</Button>
                            <Dropdown name="Dropdown" id="btnGroupDrop1" contextual={Contextual.primary}>
                                <Hyperlink>Dropdown link</Hyperlink>
                                <Hyperlink>Dropdown link</Hyperlink>
                            </Dropdown>
                        </ButtonGroup>
                    </div>
                    {/** BUTTON GROUP: DROPDOW - TODO */}
                    <div style={{padding: '5px'}}>
                        <ButtonGroup label="Button group with nested dropdown">
                            <Button contextual={Contextual.primary}>1</Button>
                            <Button contextual={Contextual.primary}>2</Button>
                            <Dropdown name="Dropdown" id="btnGroupDrop1" contextual={Contextual.primary}>
                                <Hyperlink>Dropdown link</Hyperlink>
                                <Hyperlink>Dropdown link</Hyperlink>
                            </Dropdown>
                        </ButtonGroup>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}