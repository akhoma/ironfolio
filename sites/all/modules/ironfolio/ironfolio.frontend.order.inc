<?php

function form_frontend_ironfolio_order($form, &$form_state) {

    drupal_add_js(drupal_get_path('module', 'ironfolio') .'/js/ironfolio-order-from.js');
    drupal_add_js('
jQuery(document).ready(function () {
	IronFolio.orderForm.init();
  });', 'inline');

    $formatTrqanslation = t('Format');
    $fromat = <<<EOF
    <div id="folio-formats">
        $formatTrqanslation: <a href="#">468x60</a> | <a href="#">100x100</a> | <a href="#">728x90</a> | <a href="#">600x90</a> |
        <a href="#">400x280</a> | <a href="#">240x400</a> | <a href="#">400x400</a> | <a href="#">200x200</a> |
        <a href="#">500x22</a> | <a href="#">120x240</a> | <a href="#">120x60</a> | <a href="#">300x250</a> |
        <a href="#">160x600</a> | <a href="#">760x120</a> | <a href="#">226x100</a> | <a href="#">120x120</a> |
        <a href="#">300x165</a> | <a href="#">150x150</a> | <a href="#">150x400</a> | <a href="#">200x100</a> |
        <a href="#">208x132</a> | <a href="#">234x200</a> | <a href="#">120x160</a> | <a href="#">560x120</a> |
        <a href="#">240x60</a> | <a href="#">120x600</a> | <a href="#">600x120</a> | <a href="#">600x165</a> |
        <a href="#">300x100</a> | <a href="#">88x31</a>
    </div>
EOF;


    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#required' => TRUE,
        '#prefix' => '',
        '#suffix' => '',
    );

    $form['email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#required' => TRUE,
    );

    $form['format'] = array(
        '#type' => 'textarea',
        '#title' => t('Format'),
        '#required' => TRUE,
        '#suffix' => $fromat,
    );

    $form['submit_button'] = array(
        '#type' => 'submit',
        '#value' => t('Submit order'),
    );

    return $form;
}

function form_frontend_ironfolio_order_validate($form, &$form_state) {
    $mail = $form_state['values']['email'];
    if (!valid_email_address($mail)) {
        form_set_error('email', t('Please Enter a valid email address.'));
    }
}

function ironfolio_order_mail($key, &$message, $params) {

    $headers = array(
        'MIME-Version' => '1.0',
        'Content-Type' => 'text/html; charset=UTF-8;',
        'Content-Transfer-Encoding' => '8Bit',
        'X-Mailer' => 'Drupal'
    );

    foreach ($headers as $key => $value) {
        $message['headers'][$key] = $value;
    }

    $message['subject'] = $params['subject'];
    $message['body'] = $params['body'];
}

function form_frontend_ironfolio_order_submit($form, &$form_state) {
    $name = $form_state['values']['name'];
    $valid_email = $form_state['values']['email'];
    $orderFormatText = $form_state['values']['format'];;
    $from = 'noreply@ironfolio.com';
    $body[] = '<h1>Форма заказа</h1>';
    $body[] = 'Имя: ' . $name . '<br />';
    $body[] = 'Email: ' . $valid_email . '<br />';
    $body[] = 'Формат: ' . $orderFormatText . '<br />';

    $to = variable_get('site_mail', 'an@example.com'); // Set this email address - emails will be sent to this email address!
    $params = array(
        'body' => $body,
        'subject' => 'Форма заказа (Iron Folio)',
    );

    if (drupal_mail('ironfolio_order', 'some_mail_key', $to, language_default(), $params, $from, TRUE))
    {
        drupal_set_message(t('Thanks, your data has been sent.'));
    } else {
        drupal_set_message(t('There was an error subscribing you. Please try again later'));
    }
}