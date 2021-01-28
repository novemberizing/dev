import React, { Component}  from 'react';

import Context from '../../context';

import Floating from '../../components/input/floating';
import Input from '../../components/input';
import Select from '../../components/select';
import Form from '../../components/form';

export default class ExampleFormFloatingView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type: []}}>
                <div style={{padding: '5px'}}>
                    <Form>
                        <div className="row g-2">
                            <div className="col-md">
                                <Floating>
                                    <Input type="email" id="floatingGridInput2" placeholder="name@example.com" defaultValue="name@example.com" />
                                <label htmlFor="floatingGridInput2">Email address</label>
                                </Floating>
                            </div>
                            <div className="col-md">
                                <Floating className="mb-3">
                                    <Select id="floatingGridSelect" label="floating select">
                                        <option defaultValue>Open this select menu</option>
                                        <option value="1">One</option>
                                        <option value="2">Two</option>
                                        <option value="3">Three</option>
                                    </Select>
                                    <label htmlFor="floatingGridSelect">Works with selects</label>
                                </Floating>
                            </div>
                        </div>
                        <Floating className="mb-3">
                            <Select id="floatingSelect" label="floating select">
                                <option defaultValue>Open this select menu</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                            <label htmlFor="floatingSelect">Works with selects</label>
                        </Floating>
                        <Floating className="mb-3">
                            <textarea className="form-control" placeholder="Leave a comment here" id="floatingTextarea2" style={{height: '100px'}}></textarea>
                            <label htmlFor="floatingTextarea2">Comments</label>
                        </Floating>
                        <Floating className="mb-3">
                            <textarea className="form-control" placeholder="Leave a comment here" id="floatingTextarea"></textarea>
                            <label htmlFor="floatingTextarea">Comments</label>
                        </Floating>
                        <Floating className="mb-3">
                            <Input type="email" id="floatingInput2" placeholder="name@example.com" defaultValue="name@example.com" invalid />
                            <label htmlFor="floatingInput2">Email address</label>
                        </Floating>
                        <Floating className="mb-3">
                            <Input type="email" id="floatingInput1" placeholder="name@example.com" defaultValue="name@example.com" />
                            <label htmlFor="floatingInput1">Email address</label>
                        </Floating>
                        <Floating className="mb-3">
                            <Input type="email" id="floatingInput" placeholder="name@example.com" />
                            <label htmlFor="floatingInput">Email address</label>
                        </Floating>
                        <Floating className="mb-3">
                            <Input type="password" id="floatingPassword" placeholder="Password" />
                            <label htmlFor="floatingPassword">Password</label>
                        </Floating>
                    </Form>
                </div>
            </Context.Provider>
        );
    }
}