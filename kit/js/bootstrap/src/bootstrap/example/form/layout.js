import React, { Component } from 'react';

import Context from '../../context';
import Contextual from '../../contextual';

import Label from '../../components/label';
import Form from '../../components/form';
import Input from '../../components/input';
import Select from '../../components/select';
import Button from '../../components/button';
import Check from '../../components/input/check';
import Radio from '../../components/input/radio';
import InputText from '../../components/input/text';
import InputGroup from '../../components/input/group';

export default class ExampleFormLayoutView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
                <Context.Provider value={{type: []}}>
                    <div style={{padding: '5px'}}>
                        <Form className="row row-cols-lg-auto g-3 align-items-center">
                            <div className="col-12">
                                <label className="visually-hidden" htmlFor="inlineFormInputGroupUsername">Username</label>
                                <InputGroup>
                                    <div className="input-group-text">@</div>
                                    <Input type="text" id="inlineFormInputGroupUsername" placeholder="Username" />
                                </InputGroup>
                            </div>
                            <div className="col-12">
                                <label className="visually-hidden" htmlFor="inlineFormSelectPref">Preference</label>
                                <Select id="inlineFormSelectPref">
                                    <option defaultValue>Choose...</option>
                                    <option value="1">One</option>
                                    <option value="2">Two</option>
                                    <option value="3">Three</option>
                                </Select>
                            </div>
                            <div className="col-12">
                                <Check id="inlineFormCheck">
                                    Remember me
                                </Check>
                            </div>
                            <div className="col-12">
                                <Button type="submit" contextual={Contextual.primary}>Submit</Button>
                            </div>
                        </Form>
                        <Form className="row gy-2 gx-3 align-items-center">
                            <div className="col-sm-3">
                                <label className="visually-hidden" htmlFor="autoSizingInput1-1">Name</label>
                                <Input placeholder="Jane Doe" id="autoSizingInput1-1" />
                            </div>
                            <div className="col-sm-3">
                                <label className="visually-hidden" htmlFor="autoSizingInput1-0">Username</label>
                                <InputGroup>
                                    <InputText placeholder="Jane Doe" id="autoSizingInput1-0" description="@" />
                                </InputGroup>
                            </div>
                            <div className="col-sm-3">
                                <label className="visually-hidden" htmlFor="autoSizingSelect-11">Preference</label>
                                <Select id="autoSizingSelect-11">
                                    <option defaultValue>Choose...</option>
                                    <option value="1">One</option>
                                    <option value="2">Two</option>
                                    <option value="3">Three</option>
                                </Select>
                            </div>
                            <div className="col-auto">
                                <Check id="autoSizingCheck-1">Remember me</Check>
                            </div>
                            <div className="col-auto">
                                <Button type="submit" contextual={Contextual.primary}>Submit</Button>
                            </div>
                        </Form>
                        <Form className="row gy-2 gx-3 align-items-center">
                            <div className="col-auto">
                                <label className="visually-hidden" htmlFor="autoSizingInput">Name</label>
                                <Input placeholder="Jane Doe" id="autoSizingInput" />
                            </div>
                            <div className="col-auto">
                                <label className="visually-hidden" htmlFor="autoSizingInput1">Username</label>
                                <InputGroup>
                                    <InputText placeholder="Jane Doe" id="autoSizingInput1" description="@" />
                                </InputGroup>
                            </div>
                            <div className="col-auto">
                                <label className="visually-hidden" htmlFor="autoSizingInput1">Preference</label>
                                <Select id="autoSizingSelect">
                                    <option defaultValue>Choose...</option>
                                    <option value="1">One</option>
                                    <option value="2">Two</option>
                                    <option value="3">Three</option>
                                </Select>
                            </div>
                            <div className="col-auto">
                                <Check id="autoSizingCheck">Remember me</Check>
                            </div>
                            <div className="col-auto">
                                <Button type="submit" contextual={Contextual.primary}>Submit</Button>
                            </div>
                        </Form>
                        <Form>
                            <div className="row g-3">
                                <div className="col-sm-7">
                                    <Input placeholder="City" label="City" />
                                </div>
                                <div className="col-sm">
                                    <Input placeholder="State" label="State" />
                                </div>
                                <div className="col-sm">
                                    <Input placeholder="Zip" label="State" />
                                </div>
                            </div>
                            <div className="row mb-3">
                                <label htmlFor="inputEmailSize1" className="col-sm-2 col-form-label-sm">Email</label>
                                <div className="col-sm-10">
                                    <Input type="password" id="inputEmailSize1" size={Input.sm} />
                                </div>
                            </div>
                            <div className="row mb-3">
                                <label htmlFor="inputEmailSize2" className="col-sm-2 col-form-label-lg">Email</label>
                                <div className="col-sm-10">
                                    <Input type="password" id="inputEmailSize2" size={Input.lg} />
                                </div>
                            </div>
                            <div className="row mb-3">
                                <label htmlFor="inputEmailSize3" className="col-sm-2 col-form-label">Email</label>
                                <div className="col-sm-10">
                                    <Input type="password" id="inputEmailSize3" />
                                </div>
                            </div>
                            <div className="row mb-3">
                                <label htmlFor="inputEmail3" className="col-sm-2 col-form-label">Email</label>
                                <div className="col-sm-10">
                                    <Input type="email" id="inputEmail3" />
                                </div>
                            </div>
                            <div className="row mb-3">
                                <label htmlFor="inputEmail4" className="col-sm-2 col-form-label">Password</label>
                                <div className="col-sm-10">
                                    <Input type="password" id="inputEmail4" />
                                </div>
                            </div>
                            <div className="row mb-3">
                                <legend className="col-form-label col-sm-2 pt-0">Radios</legend>
                                <div className="col-sm-10">
                                    <Radio name="gridRadios" id="gridRadios1">Grid Radio</Radio>
                                    <Radio name="gridRadios" id="gridRadios2">Grid Radio</Radio>
                                    <Radio name="gridRadios" id="gridRadios3" disabled>Grid Radio</Radio>
                                </div>
                            </div>
                            <div className="row mb-3">
                                <legend className="col-form-label col-sm-2 pt-0">Checkbox</legend>
                                <div className="col-sm-10">
                                    <Check id="gridCheck1">Grid Checkbox</Check>
                                </div>
                            </div>
                            <button type="submit" className="btn btn-primary">Sign in</button>

                            <div className="row g-3">
                                <div className="col-md-6">
                                    <Label htmlFor="formGroupExampleInput7">Email</Label>
                                    <Input type="email" id="formGroupExampleInput7"></Input>
                                </div>
                                <div className="col-md-6">
                                    <Label htmlFor="formGroupExampleInput6">Password</Label>
                                    <Input type="password" id="formGroupExampleInput6" placeholder="name@email.com"></Input>
                                </div>
                                <div className="col-12">
                                    <Label htmlFor="formGroupExampleInput8">Address</Label>
                                    <Input type="text" id="formGroupExampleInput8"></Input>
                                </div>
                                <div className="col-md-6">
                                    <Label htmlFor="formGroupExampleInput9">City</Label>
                                    <Input type="text" id="formGroupExampleInput9"></Input>
                                </div>
                                <div className="col-md-4">
                                    <Label htmlFor="formGroupExampleInput10">State</Label>
                                    <Select id="formGroupExampleInput10">
                                        <option defaultValue>Choose...</option>
                                        <option>...</option>
                                    </Select>
                                </div>
                                <div className="col-md-2">
                                    <Label htmlFor="formGroupExampleInput11">Zip</Label>
                                    <Input type="text" id="formGroupExampleInput11"></Input>
                                </div>
                                <div className="col-12">
                                    <Check id="formGroupExampleInput12">Check me out</Check>
                                </div>
                                <div className="col-12">
                                    <Button type="submit" contextual={Contextual.primary}>Sign in</Button>
                                </div>
                            </div>
                            <div className="row g-3">
                                <div className="col">
                                    <Input id="formGroupExampleInput5" placeholder="First"></Input>
                                </div>
                                <div className="col">
                                    <Input id="formGroupExampleInput4" placeholder="Last"></Input>
                                </div>
                            </div>
                            <div className="row">
                                <div className="col">
                                    <Input id="formGroupExampleInput3" placeholder="First"></Input>
                                </div>
                                <div className="col">
                                    <Input id="formGroupExampleInput2" placeholder="Last"></Input>
                                </div>
                            </div>
                            <div className="mb-3">
                                <Label htmlFor="formGroupExampleInput">Example Label</Label>
                                <Input id="formGroupExampleInput" placeholder="Example Label"></Input>
                            </div>
                            <div className="mb-3">
                                <Label htmlFor="formGroupExampleInput1">Example Another Label</Label>
                                <Input id="formGroupExampleInput1" placeholder="Example another Label"></Input>
                            </div>   
                        </Form>
                    </div>
                </Context.Provider>
        );
    }
}
