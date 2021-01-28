import React, { Component } from 'react';

import Form from '../../components/form';
import Input from '../../components/input';
import Label from '../../components/label';
import Button from '../../components/button';
import Text from '../../components/text';
import Select from '../../components/select';
import Check from '../../components/input/check';

import Contextual from '../../contextual';
import Context from '../../context';

export default class ExampleFormView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    <div style={{padding: '5px'}}>
                        <Form className="row g-3 needs-validation">
                            <div className="col-md-4">
                                <label htmlFor="validationCustom01" className="form-label">First name</label>
                                <Input id="validationCustom01" defaultValue="Mark" required />
                                <div className="valid-feedback">
                                    Looks good!
                                </div>
                            </div>
                            <div className="col-md-4">
                                <label htmlFor="validationCustom02" className="form-label">Last name</label>
                                <Input id="validationCustom02" defaultValue="Otto" required />
                                <div className="valid-feedback">
                                    Looks good!
                                </div>
                            </div>
                            <div className="col-md-4">
                                <label htmlFor="validationCustomUsername" className="form-label">Username</label>
                                <div className="input-group has-validation">
                                    <Input id="validationCustomUsername" description="@" required />
                                    <div className="invalid-feedback">
                                        Please choose a username.
                                    </div>
                                </div>
                            </div>
                            <div className="col-md-6">
                                <label htmlFor="validationCustom03" className="form-label">City</label>
                                <Input id="validationCustom03" required />
                                <div className="invalid-feedback">
                                    Please provide a valid city.
                                </div>
                            </div>
                            <div className="col-md-3">
                                <label htmlFor="validationCustom04" className="form-label">State</label>
                                <Select id="validationCustom04" required>
                                    <option defaultValue disabled value="">Choose...</option>
                                    <option value="1">...</option>
                                </Select>
                                <div className="invalid-feedback">
                                    Please select a valid state.
                                </div>
                            </div>
                            <div className="col-md-3">
                                <label htmlFor="validationCustom05" className="form-label">Zip</label>
                                <Input id="validationCustom05" required></Input>
                                <div className="invalid-feedback">
                                    Please provide a valid zip.
                                </div>
                            </div>
                            <div className="col-12">
                                <Check id="invalidCheck">Agree to terms and conditions</Check>
                                <div className="invalid-feedback">
                                    You must agree before submitting.
                                </div>
                            </div>
                            <div className="col-12">
                                <button className="btn btn-primary" type="submit">Submit form</button>
                            </div>
                        </Form>
                    </div>
                    {/** FORM: DISABLE FIELDSET */}
                    <Form disabled>
                        <legend>Disabled fieldset example</legend>
                        <div className="mb-3">
                            <label htmlFor="disabledTextInput" className="form-label">Disabled input</label>
                            <input type="text" id="disabledTextInput" className="form-control" placeholder="Disabled input" />
                        </div>
                        <div className="mb-3">
                            <label htmlFor="disabledSelect" className="form-label">Disabled select menu</label>
                            <select id="disabledSelect" className="form-select">
                                <option>Disabled select</option>
                            </select>
                        </div>
                        <div className="mb-3">
                            <div className="form-check">
                                <input className="form-check-input" type="checkbox" id="disabledFieldsetCheck" disabled />
                                <label className="form-check-label" htmlFor="disabledFieldsetCheck">
                                    Can't check this
                                </label>
                            </div>
                        </div>
                        <button type="submit" className="btn btn-primary">Submit</button>
                    </Form>
                    {/** FORM: DISABLE */}
                    <Form>
                        <Input type="text" id="disabledInput" placeholder="Disabled input here..." disabled />
                    </Form>
                    {/** FORM: TEXT */}
                    <Form>
                        <div className="row g-3 align-items-center">
                            <div className="col-auto">
                                <Label htmlFor="inputPassword6">Password</Label>
                            </div>
                            <div className="col-auto">
                                <Input type="password" id="inputPassword6" aria-describedby="passwordHelpInline"></Input>
                            </div>
                            <div className="col-auto">
                                <span id="passwordHelpInline" className="form-text">
                                    Must be 8-20 characters long.
                                </span>
                            </div>
                        </div>
                    </Form>
                    <Form>
                        <Label htmlFor="inputPassword5">Password</Label>
                        <Input type="password" id="inputPassword5" aria-describedby="passwordHelpBlock" />
                        <Text id="passwordHelpBlock">
                            Your password must be 8-20 characters long, contain letters and numbers, and must not contain spaces, special characters, or emoji.
                        </Text>
                    </Form>
                    {/** FORM */}
                    <Form>
                        <div className="mb-3">
                            <Label htmlFor="exampleInputEmail1">Email address</Label>
                            <Input type="email" id="exampleInputEmail1" aria-describedby="emailHelp" />
                            <Text id="emailHelp">We'll never share your email with anyone else.</Text>
                        </div>
                        <div className="mb-3">
                            <Label htmlFor="exampleInputPassword1">Password</Label>
                            <Input type="password" id="exampleInputPassword1"></Input>
                        </div>
                        <div className="mb-3 form-check">
                            <Input type="checkbox" id="exampleCheck1" />
                            <Label htmlFor="exampleCheck1" className="form-check-label">Check me out</Label>
                        </div>
                        <Button type="submit" contextual={Contextual.primary}>Submit</Button>
                    </Form>
                </div>
            </Context.Provider>
        );
    }
}