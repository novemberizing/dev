import React, { Component } from 'react';

import Select from '../../components/select';
import Form from '../../components/form';
import Context from '../../context';

export default class ExampleFormSelectView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** SELECT: DISABLED */}
                    <div style={{padding: '5px'}}>
                        <Form>
                            <Select label="Default select example" size={Select.lg} multiple={3} disabled>
                                <option defaultValue>Open this select menu</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                        </Form>                    
                    </div>
                    {/** SELECT: MULTIPLE */}
                    <div style={{padding: '5px'}}>
                        <Form>
                            <Select label="Default select example" size={Select.lg} multiple={3}>
                                <option defaultValue>Open this select menu</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                        </Form>                    
                    </div>
                    {/** SELECT: SIZE */}
                    <div style={{padding: '5px'}}>
                        <Form>
                            <Select label="Default select example" size={Select.lg}>
                                <option defaultValue>Open this select menu</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                        </Form>
                    </div>
                    <div style={{padding: '5px'}}>
                        <Form>
                            <Select label="Default select example" size={Select.sm}>
                                <option defaultValue>Open this select menu</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                        </Form>
                    </div>
                    {/** SELECT */}
                    <div style={{padding: '5px'}}>
                        <Form>
                            <Select label="Default select example">
                                <option defaultValue>Open this select menu</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                        </Form>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}