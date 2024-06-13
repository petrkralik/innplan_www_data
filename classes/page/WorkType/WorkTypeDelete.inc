<?php


namespace page\WorkType;


class WorkTypeDelete extends WorkType
{


	const string ACTION_CONFIRMATION = "confirmation";

	const string ACTION_PROCESSING = "processing";


	function getContentMain(): ?\iw\dom\Element
	{
		$dom= null;
		if($this->detectProcess()== self::ACTION_PROCESSING) {
			$dom= $this->delete();
		} else {

			// Confirmation
			$this->getWorkTypeId();
			$dom= $this->domConfirmation();
		}

		return $this->dom->div(\N, $dom);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 */
	private function delete(): bool
	{
		return $this->getBusinessObject()->delete();
	}



	private function detectProcess(): string
	{
		return match ($this->uriMatches[2] ?? null) {
			"processing" => self::ACTION_PROCESSING,
			default => self::ACTION_CONFIRMATION,
		};
	}


	private function domConfirmation(): array
	{
		return [
			$this->dom->p(\N, "Opravdu chcete tento ty práce smazat?"),
			$this->domButtonBack(),
			$this->domButtonConfirm(),
		];
	}


	private function domButtonBack(): \iw\dom\Element
	{
		return $this->dom->a(\N, \urlBasePage. "/workType/{$this->getWorkTypeId()}", "nemazat");
	}


	private function domButtonConfirm(): \iw\dom\Element
	{
		return $this->dom->a(\N, \urlBasePage. "/workType/{$this->getWorkTypeId()}/delete/processing", "ano, smazat");
	}


}