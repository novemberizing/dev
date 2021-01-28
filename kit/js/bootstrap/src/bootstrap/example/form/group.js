import React, { Component } from 'react';

import Context from '../../context';
import Contextual from '../../contextual';

import Form from '../../components/form';
import InputGroup from '../../components/input/group';
import Button from '../../components/button';
import Check from '../../components/input/check';
import Radio from '../../components/input/radio';
import Input from '../../components/input';
import InputText from '../../components/input/text';
import Select from '../../components/select';
import Dropdown from '../../components/dropdown';
import Hyperlink from '../../components/hyperlink';
import Divider from '../../components/divider';
import Label from '../../components/label';

export default class ExampleFormGroupView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type: []}}>
                <div style={{padding:'5px'}}>
                    <Form>
                        <InputGroup className="mb-3">
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                            <Input type="file" id="inputGroupFile04"></Input>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Input type="file" id="inputGroupFile03"></Input>
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Input type="file" id="inputGroupFile02"></Input>
                            <label className="input-group-text" htmlFor="inputGroupFile02">Upload</label>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <label className="input-group-text" htmlFor="inputGroupFile01">Upload</label>
                            <Input type="file" id="inputGroupFile01"></Input>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                            <Select id="inputGroupSelect04">
                                <option defaultValue>Choose...</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Select id="inputGroupSelect03">
                                <option defaultValue>Choose...</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Select id="inputGroupSelect02">
                                <option defaultValue>Choose...</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                            <label className="input-group-text" htmlFor="inputGroupSelect02">Options</label>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <label className="input-group-text" htmlFor="inputGroupSelect01">Options</label>
                            <Select id="inputGroupSelect01">
                                <option defaultValue>Choose...</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </Select>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Dropdown id="username26dropdown" name="Dropdown" contextual={Contextual.secondary} outline split>
                                <Hyperlink>Active</Hyperlink>
                                <Hyperlink>InActive</Hyperlink>
                                <Divider></Divider>
                                <Hyperlink>Split</Hyperlink>
                            </Dropdown>
                            <InputText id="username26" placeholder="Recipient's username" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username25" placeholder="Recipient's username" />
                            <Dropdown id="username25dropdown" name="Dropdown" contextual={Contextual.secondary} outline split>
                                <Hyperlink>Active</Hyperlink>
                                <Hyperlink>InActive</Hyperlink>
                                <Divider></Divider>
                                <Hyperlink>Split</Hyperlink>
                            </Dropdown>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Dropdown id="username29dropdown" name="Dropdown" contextual={Contextual.secondary} outline>
                                <Hyperlink>Active</Hyperlink>
                                <Hyperlink>InActive</Hyperlink>
                                <Divider></Divider>
                                <Hyperlink>Split</Hyperlink>
                            </Dropdown>
                            <InputText id="username24" placeholder="Recipient's username" />
                            <Dropdown id="username23dropdown" name="Dropdown" contextual={Contextual.secondary} outline>
                                <Hyperlink>Active</Hyperlink>
                                <Hyperlink>InActive</Hyperlink>
                                <Divider></Divider>
                                <Hyperlink>Split</Hyperlink>
                            </Dropdown>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username22" placeholder="Recipient's username" />
                            <Dropdown id="username22dropdown" name="Dropdown" contextual={Contextual.secondary} outline>
                                <Hyperlink>Active</Hyperlink>
                                <Hyperlink>InActive</Hyperlink>
                                <Divider></Divider>
                                <Hyperlink>Split</Hyperlink>
                            </Dropdown>
                        </InputGroup>

                        <InputGroup className="mb-3">
                            <Dropdown id="username21dropdown" name="Dropdown" contextual={Contextual.secondary} outline>
                                <Hyperlink>Active</Hyperlink>
                                <Hyperlink>InActive</Hyperlink>
                                <Divider></Divider>
                                <Hyperlink>Split</Hyperlink>
                            </Dropdown>
                            <InputText id="username21" placeholder="Recipient's username" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username20" placeholder="Recipient's username" />
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                            <InputText id="username19" placeholder="Recipient's username" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username18" placeholder="Recipient's username" />
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <Button contextual={Contextual.secondary} outline>Button</Button>
                            <InputText id="username17" placeholder="Recipient's username" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username16" placeholder="Recipient's username" />
                            <span className="input-group-text">$</span>
                            <span className="input-group-text">0.00</span>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <span className="input-group-text">$</span>
                            <span className="input-group-text">0.00</span>
                            <InputText id="username30" placeholder="Recipient's username" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <span className="input-group-text">First and last name</span>
                            <InputText id="username14" placeholder="Recipient's username" />
                            <InputText id="username15" placeholder="Recipient's username" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <div className="input-group-text">
                                <Radio id="username13check"></Radio>
                            </div>
                            <InputText id="username13" placeholder="Recipient's username" label="Recipient's username" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <div className="input-group-text">
                                <Check id="username12check"></Check>
                            </div>
                            <InputText id="username12" placeholder="Recipient's username" label="Recipient's username" />
                        </InputGroup>
                        <InputGroup className="mb-3" size={InputGroup.sm}>
                            <InputText id="username11" placeholder="Recipient's username" label="Recipient's username" description="small" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username10" placeholder="Recipient's username" label="Recipient's username" description="default" />
                        </InputGroup>
                        <InputGroup className="mb-3" size={InputGroup.lg}>
                            <InputText id="username9" placeholder="Recipient's username" label="Recipient's username" description="large" />
                        </InputGroup>
                        <InputGroup className="mb-3" nowrap>
                            <InputText id="username8" placeholder="Recipient's username" label="Recipient's username" description={{text:"@example.com", pos: 'right'}} />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <span className="input-group-text">With textarea</span>
                            <textarea className="form-control" aria-label="with textarea"></textarea>
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username7" placeholder="Username" label="Amount (to the nearest dollar)" />
                            <span className="input-group-text">@</span>
                            <InputText id="username6" placeholder="Server" label="Amount (to the nearest dollar)" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <span className="input-group-text">$</span>
                            <InputText id="username5" label="Amount (to the nearest dollar)" />
                            <span className="input-group-text">.00</span>
                        </InputGroup>
                        <Label htmlFor="basic-url">Your verity URL</Label>
                        <InputGroup className="mb-3">
                            <InputText id="username4" placeholder="basic-url" label="basic-url" description="https://example.com/users/" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username3" placeholder="Username" label="Username" description="@" />
                        </InputGroup>
                        <InputGroup className="mb-3">
                            <InputText id="username2" placeholder="Recipient's username" label="Recipient's username" description={{text:"@example.com", pos: 'right'}} />
                        </InputGroup>
                    </Form>
                </div>
            </Context.Provider>
        );
    }
}
