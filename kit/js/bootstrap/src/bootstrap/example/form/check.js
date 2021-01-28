/**
 * 
 */
import React, { Component } from 'react';

import Form from '../../components/form';
import Check from '../../components/input/check';
import Radio from '../../components/input/radio';
import Context from '../../context';

export default class ExampleFormCheckView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** WITHOUT LABEL */}
                    <div style={{padding: '5px'}}>
                        <Form>
                            <Check id="flexCheckDefault17" />
                            <Check id="flexCheckDefault27" />
                        </Form>
                    </div>
                    {/** INLINE */}
                        <Form>
                            {/** TODO: HOW TO INDETERMINATE */}
                            <Radio id="flexRadioIndeterminate6" name="flexRadioDefault6" value="" inline>Indeterminate checkbox</Radio>
                            <Radio id="flexRadioIndeterminate26" name="flexRadioDefault6" value="" inline defaultChecked>Indeterminate checkbox</Radio>
                            <Radio id="flexRadioDefault6" name="flexRadioDefault6" disabled inline>Default checkbox</Radio>
                        </Form>
                    {/** INLINE */}
                        <Form>
                            {/** TODO: HOW TO INDETERMINATE */}
                            <Check id="flexCheckIndeterminate4" value="" inline>Indeterminate checkbox</Check>
                            <Check id="flexCheckIndeterminate24" value="" inline defaultChecked>Indeterminate checkbox</Check>
                            <Check id="flexCheckDefault4" disabled inline>Default checkbox</Check>
                        </Form>
                    {/** SWITCH */}
                    <div style={{padding: '5px'}}>
                        <Form>
                            {/** TODO: HOW TO INDETERMINATE */}
                            <Check id="flexCheckIndeterminate3" value="" switching>Indeterminate checkbox</Check>
                            <Check id="flexCheckIndeterminate23" value="" switching defaultChecked>Indeterminate checkbox</Check>
                            <Check id="flexCheckDefault3" disabled switching>Default checkbox</Check>
                        </Form>
                    </div>
                    {/** RADIO: DISABLED */}
                    <div style={{padding: '5px'}}>
                        <Form>
                            <Radio id="flexRadioDefault3" name="flexRadioDefault1" value="" disabled>Default radio</Radio>
                            <Radio id="flexRadioDefault4" name="flexRadioDefault1" value="" defaultChecked disabled>Default checked radio</Radio>
                        </Form>
                    </div>
                    {/** RADIO */}
                    <div style={{padding: '5px'}}>
                        <Form>
                            <Radio id="flexRadioDefault1" name="flexRadioDefault" value="">Default radio</Radio>
                            <Radio id="flexRadioDefault2" name="flexRadioDefault" value="" defaultChecked>Default checked radio</Radio>
                        </Form>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Form>
                            {/** TODO: HOW TO INDETERMINATE */}
                            <Check id="flexCheckIndeterminate2" value="" disabled>Indeterminate checkbox</Check>
                            <Check id="flexCheckDefault2" disabled>Default checkbox</Check>
                            <Check id="flexCheckChecked2" defaultChecked disabled>Checked checkbox</Check>
                        </Form>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Form>
                            {/** TODO: HOW TO INDETERMINATE */}
                            <Check id="flexCheckIndeterminate" value="">Indeterminate checkbox</Check>
                            <Check id="flexCheckDefault">Default checkbox</Check>
                            <Check id="flexCheckChecked" defaultChecked>Checked checkbox</Check>
                        </Form>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}